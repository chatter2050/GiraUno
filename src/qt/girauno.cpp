// Copyright (c) 2016-2019 The Girauno developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "girauno-config.h"
#endif

#include "giraunogui.h"

#include "clientmodel.h"
#include "guiconstants.h"
#include "guiutil.h"
#include "intro.h"
#include "optionsmodel.h"
#include "splashscreen.h"
#include "utilitydialog.h"
#include "winshutdownmonitor.h"
#ifdef ENABLE_WALLET
#include "paymentserver.h"
#include "walletmodel.h"
#endif

#include "init.h"
#include "main.h"
#include "rpcserver.h"
#include "ui_interface.h"
#include "util.h"
#ifdef ENABLE_WALLET
#include "wallet.h"
#endif

#include <stdint.h>

#include <boost/filesystem/operations.hpp>
#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <QTranslator>
#include <QThread>

#if defined(QT_STATICPLUGIN)
#include <QtPlugin>
#if QT_VERSION < 0x050000
Q_IMPORT_PLUGIN(qcncodecs)
Q_IMPORT_PLUGIN(qjpcodecs)
Q_IMPORT_PLUGIN(qtwcodecs)
Q_IMPORT_PLUGIN(qkrcodecs)
Q_IMPORT_PLUGIN(qtaccessiblewidgets)
#else
Q_IMPORT_PLUGIN(AccessibleFactory)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif
#endif

#if QT_VERSION < 0x050000
#include <QTextCodec>
#endif

// Declare meta types used for QMetaObject::invokeMethod
Q_DECLARE_METATYPE(bool*)

static void InitMessage(const std::string &message)
{
    LogPrintf("init message: %s\n", message);
}

/*
   Translate string to current locale using Qt.
 */
static std::string Translate(const char* psz)
{
    return QCoreApplication::translate("girauno-core", psz).toStdString();
}

/** Set up translations */
static void initTranslations(QTranslator &qtTranslatorBase, QTranslator &qtTranslator, QTranslator &translatorBase, QTranslator &translator)
{
    QSettings settings;

    // Remove old translators
    QApplication::removeTranslator(&qtTranslatorBase);
    QApplication::removeTranslator(&qtTranslator);
    QApplication::removeTranslator(&translatorBase);
    QApplication::removeTranslator(&translator);

    // Get desired locale (e.g. "de_DE")
    // 1) System default language
    QString lang_territory = QLocale::system().name();
    // 2) Language from QSettings
    QString lang_territory_qsettings = settings.value("language", "").toString();
    if(!lang_territory_qsettings.isEmpty())
        lang_territory = lang_territory_qsettings;
    // 3) -lang command line argument
    lang_territory = QString::fromStdString(GetArg("-lang", lang_territory.toStdString()));

    // Convert to "de" only by truncating "_DE"
    QString lang = lang_territory;
    lang.truncate(lang_territory.lastIndexOf('_'));

    // Load language files for configured locale:
    // - First load the translator for the base language, without territory
    // - Then load the more specific locale translator

    // Load e.g. qt_de.qm
    if (qtTranslatorBase.load("qt_" + lang, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        QApplication::installTranslator(&qtTranslatorBase);

    // Load e.g. qt_de_DE.qm
    if (qtTranslator.load("qt_" + lang_territory, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        QApplication::installTranslator(&qtTranslator);

    // Load e.g. girauno_de.qm (shortcut "de" needs to be defined in girauno.qrc)
    if (translatorBase.load(lang, ":/translations/"))
        QApplication::installTranslator(&translatorBase);

    // Load e.g. girauno_de_DE.qm (shortcut "de_DE" needs to be defined in girauno.qrc)
    if (translator.load(lang_territory, ":/translations/"))
        QApplication::installTranslator(&translator);
}

/* qDebug() message handler --> debug.log */
#if QT_VERSION < 0x050000
void DebugMessageHandler(QtMsgType type, const char *msg)
{
    Q_UNUSED(type);
    LogPrint("qt", "GUI: %s\n", msg);
}
#else
void DebugMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);
    LogPrint("qt", "GUI: %s\n", qPrintable(msg));
}
#endif

/** Class encapsulating Girauno Core startup and shutdown.
 * Allows running startup and shutdown in a different thread from the UI thread.
 */
class GiraunoCore: public QObject
{
    Q_OBJECT
public:
    explicit GiraunoCore();

public slots:
    void initialize();
    void shutdown();

signals:
    void initializeResult(int retval);
    void shutdownResult(int retval);
    void runawayException(const QString &message);

private:
    boost::thread_group threadGroup;

    /// Pass fatal exception message to UI thread
    void handleRunawayException(std::exception *e);
};

/** Main Girauno application object */
class GiraunoApplication: public QApplication
{
    Q_OBJECT
public:
    explicit GiraunoApplication(int &argc, char **argv);
    ~GiraunoApplication();

#ifdef ENABLE_WALLET
    /// Create payment server
    void createPaymentServer();
#endif
    /// Create options model
    void createOptionsModel();
    /// Create main window
    void createWindow(bool isaTestNet);
    /// Create splash screen
    void createSplashScreen(bool isaTestNet);

    /// Request core initialization
    void requestInitialize();
    /// Request core shutdown
    void requestShutdown();

    /// Get process return value
    int getReturnValue() { return returnValue; }

    /// Get window identifier of QMainWindow (GiraunoGUI)
    WId getMainWinId() const;

public slots:
    void initializeResult(int retval);
    void shutdownResult(int retval);
    /// Handle runaway exceptions. Shows a message box with the problem and quits the program.
    void handleRunawayException(const QString &message);

signals:
    void requestedInitialize();
    void requestedShutdown();
    void stopThread();
    void splashFinished(QWidget *window);

private:
    QThread *coreThread;
    OptionsModel *optionsModel;
    ClientModel *clientModel;
    GiraunoGUI *window;
    QTimer *pollShutdownTimer;
#ifdef ENABLE_WALLET
    PaymentServer* paymentServer;
    WalletModel *walletModel;
#endif
    int returnValue;

    void startThread();
};

#include "girauno.moc"

GiraunoCore::GiraunoCore():
    QObject()
{
}

void GiraunoCore::handleRunawayException(std::exception *e)
{
    PrintExceptionContinue(e, "Runaway exception");
    emit runawayException(QString::fromStdString(strMiscWarning));
}

void GiraunoCore::initialize()
{
    try
    {
        LogPrintf("Running AppInit2 in thread\n");
        int rv = AppInit2(threadGroup);
        if(rv)
        {
            /* Start a dummy RPC thread if no RPC thread is active yet
             * to handle timeouts.
             */
            StartDummyRPCThread();
        }
        emit initializeResult(rv);
    } catch (std::exception& e) {
        handleRunawayException(&e);
    } catch (...) {
        handleRunawayException(NULL);
    }
}

void GiraunoCore::shutdown()
{
    try
    {
        LogPrintf("Running Shutdown in thread\n");
        threadGroup.interrupt_all();
        threadGroup.join_all();
        Shutdown();
        LogPrintf("Shutdown finished\n");
        emit shutdownResult(1);
    } catch (std::exception& e) {
        handleRunawayException(&e);
    } catch (...) {
        handleRunawayException(NULL);
    }
}

GiraunoApplication::GiraunoApplication(int &argc, char **argv):
    QApplication(argc, argv),
    coreThread(0),
    optionsModel(0),
    clientModel(0),
    window(0),
    pollShutdownTimer(0),
#ifdef ENABLE_WALLET
    paymentServer(0),
    walletModel(0),
#endif
    returnValue(0)
{
    setQuitOnLastWindowClosed(false);
    startThread();
}

GiraunoApplication::~GiraunoApplication()
{
    LogPrintf("Stopping thread\n");
    emit stopThread();
    coreThread->wait();
    LogPrintf("Stopped thread\n");

    delete window;
    window = 0;
#ifdef ENABLE_WALLET
    delete paymentServer;
    paymentServer = 0;
#endif
    delete optionsModel;
    optionsModel = 0;
}

#ifdef ENABLE_WALLET
void GiraunoApplication::createPaymentServer()
{
    paymentServer = new PaymentServer(this);
}
#endif

void GiraunoApplication::createOptionsModel()
{
    optionsModel = new OptionsModel();
}

void GiraunoApplication::createWindow(bool isaTestNet)
{
    window = new GiraunoGUI(isaTestNet, 0);

    pollShutdownTimer = new QTimer(window);
    connect(pollShutdownTimer, SIGNAL(timeout()), window, SLOT(detectShutdown()));
    pollShutdownTimer->start(200);
}

void GiraunoApplication::createSplashScreen(bool isaTestNet)
{
    SplashScreen *splash = new SplashScreen(QPixmap(), 0, isaTestNet);
    splash->setAttribute(Qt::WA_DeleteOnClose);
    splash->show();
    connect(this, SIGNAL(splashFinished(QWidget*)), splash, SLOT(slotFinish(QWidget*)));
}

void GiraunoApplication::startThread()
{
    coreThread = new QThread(this);
    GiraunoCore *executor = new GiraunoCore();
    executor->moveToThread(coreThread);

    /*  communication to and from thread */
    connect(executor, SIGNAL(initializeResult(int)), this, SLOT(initializeResult(int)));
    connect(executor, SIGNAL(shutdownResult(int)), this, SLOT(shutdownResult(int)));
    connect(executor, SIGNAL(runawayException(QString)), this, SLOT(handleRunawayException(QString)));
    connect(this, SIGNAL(requestedInitialize()), executor, SLOT(initialize()));
    connect(this, SIGNAL(requestedShutdown()), executor, SLOT(shutdown()));
    /*  make sure executor object is deleted in its own thread */
    connect(this, SIGNAL(stopThread()), executor, SLOT(deleteLater()));
    connect(this, SIGNAL(stopThread()), coreThread, SLOT(quit()));

    coreThread->start();
}

void GiraunoApplication::requestInitialize()
{
    LogPrintf("Requesting initialize\n");
    emit requestedInitialize();
}

void GiraunoApplication::requestShutdown()
{
    LogPrintf("Requesting shutdown\n");
    window->hide();
    window->setClientModel(0);
    pollShutdownTimer->stop();

#ifdef ENABLE_WALLET
    window->removeAllWallets();
    delete walletModel;
    walletModel = 0;
#endif
    delete clientModel;
    clientModel = 0;

    // Show a simple window indicating shutdown status
    ShutdownWindow::showShutdownWindow(window);

    // Request shutdown from core thread
    emit requestedShutdown();
}

void GiraunoApplication::initializeResult(int retval)
{
    LogPrintf("Initialization result: %i\n", retval);
    // Set exit result: 0 if successful, 1 if failure
    returnValue = retval ? 0 : 1;
    if(retval)
    {
#ifdef ENABLE_WALLET
        PaymentServer::LoadRootCAs();
        paymentServer->setOptionsModel(optionsModel);
#endif

        emit splashFinished(window);

        clientModel = new ClientModel(optionsModel);
        window->setClientModel(clientModel);

#ifdef ENABLE_WALLET
        if(pwalletMain)
        {
            walletModel = new WalletModel(pwalletMain, optionsModel);

            window->addWallet("~Default", walletModel);
            window->setCurrentWallet("~Default");

            connect(walletModel, SIGNAL(coinsSent(CWallet*,SendCoinsRecipient,QByteArray)),
                             paymentServer, SLOT(fetchPaymentACK(CWallet*,const SendCoinsRecipient&,QByteArray)));
        }
#endif

        // If -min option passed, start window minimized.
        if(GetBoolArg("-min", false))
        {
            window->showMinimized();
        }
        else
        {
            window->show();
        }
#ifdef ENABLE_WALLET
        // Now that initialization/startup is done, process any command-line
        // girauno: URIs or payment requests:
        connect(paymentServer, SIGNAL(receivedPaymentRequest(SendCoinsRecipient)),
                         window, SLOT(handlePaymentRequest(SendCoinsRecipient)));
        connect(window, SIGNAL(receivedURI(QString)),
                         paymentServer, SLOT(handleURIOrFile(QString)));
        connect(paymentServer, SIGNAL(message(QString,QString,unsigned int)),
                         window, SLOT(message(QString,QString,unsigned int)));
        QTimer::singleShot(100, paymentServer, SLOT(uiReady()));
#endif
    } else {
        quit(); // Exit main loop
    }
}

void GiraunoApplication::shutdownResult(int retval)
{
    LogPrintf("Shutdown result: %i\n", retval);
    quit(); // Exit main loop after shutdown finished
}

void GiraunoApplication::handleRunawayException(const QString &message)
{
    QMessageBox::critical(0, "Runaway exception", GiraunoGUI::tr("A fatal error occurred. Girauno can no longer continue safely and will quit.") + QString("\n\n") + message);
    ::exit(1);
}

WId GiraunoApplication::getMainWinId() const
{
    if (!window)
        return 0;

    return window->winId();
}

#ifndef GIRAUNO_QT_TEST
int main(int argc, char *argv[])
{
    SetupEnvironment();

    /// 1. Parse command-line options. These take precedence over anything else.
    // Command-line options take precedence:
    ParseParameters(argc, argv);

    // Do not refer to data directory yet, this can be overridden by Intro::pickDataDirectory

    /// 2. Basic Qt initialization (not dependent on parameters or configuration)
#if QT_VERSION < 0x050000
    // Internal string conversion is all UTF-8
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForTr());
#endif

    Q_INIT_RESOURCE(girauno);

    GUIUtil::SubstituteFonts();

    GiraunoApplication app(argc, argv);
#if QT_VERSION > 0x050100
    // Generate high-dpi pixmaps
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#ifdef Q_OS_MAC
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

    // Register meta types used for QMetaObject::invokeMethod
    qRegisterMetaType< bool* >();

    /// 3. Application identification
    // must be set before OptionsModel is initialized or translations are loaded,
    // as it is used to locate QSettings
    QApplication::setOrganizationName(QAPP_ORG_NAME);
    QApplication::setOrganizationDomain(QAPP_ORG_DOMAIN);
    QApplication::setApplicationName(QAPP_APP_NAME_DEFAULT);

    /// 4. Initialization of translations, so that intro dialog is in user's language
    // Now that QSettings are accessible, initialize translations
    QTranslator qtTranslatorBase, qtTranslator, translatorBase, translator;
    initTranslations(qtTranslatorBase, qtTranslator, translatorBase, translator);
    uiInterface.Translate.connect(Translate);

    // Show help message immediately after parsing command-line options (for "-lang") and setting locale,
    // but before showing splash screen.
    if (mapArgs.count("-?") || mapArgs.count("--help"))
    {
        HelpMessageDialog help(NULL);
        help.showOrPrint();
        return 1;
    }

    /// 5. Now that settings and translations are available, ask user for data directory
    // User language is set up: pick a data directory
    Intro::pickDataDirectory();

    /// 6. Determine availability of data directory and parse girauno.conf
    /// - Do not call GetDataDir(true) before this step finishes
    if (!boost::filesystem::is_directory(GetDataDir(false)))
    {
        QMessageBox::critical(0, QObject::tr("Girauno"),
                              QObject::tr("Error: Specified data directory \"%1\" does not exist.").arg(QString::fromStdString(mapArgs["-datadir"])));
        return 1;
    }
    try {
        ReadConfigFile(mapArgs, mapMultiArgs);
    } catch(std::exception &e) {
        QMessageBox::critical(0, QObject::tr("Girauno"),
                              QObject::tr("Error: Cannot parse configuration file: %1. Only use key=value syntax.").arg(e.what()));
        return false;
    }

    /// 7. Determine network (and switch to network specific options)
    // - Do not call Params() before this step
    // - Do this after parsing the configuration file, as the network can be switched there
    // - QSettings() will use the new application name after this, resulting in network-specific settings
    // - Needs to be done before createOptionsModel

    // Check for -testnet or -regtest parameter (Params() calls are only valid after this clause)
    if (!SelectParamsFromCommandLine()) {
        QMessageBox::critical(0, QObject::tr("Girauno"), QObject::tr("Error: Invalid combination of -regtest and -testnet."));
        return 1;
    }
#ifdef ENABLE_WALLET
    // Parse URIs on command line -- this can affect Params()
    if (!PaymentServer::ipcParseCommandLine(argc, argv))
        exit(0);
#endif
    bool isaTestNet = Params().NetworkID() != CChainParams::MAIN;
    // Allow for separate UI settings for testnets
    if (isaTestNet)
        QApplication::setApplicationName(QAPP_APP_NAME_TESTNET);
    else
        QApplication::setApplicationName(QAPP_APP_NAME_DEFAULT);
    // Re-initialize translations after changing application name (language in network-specific settings can be different)
    initTranslations(qtTranslatorBase, qtTranslator, translatorBase, translator);

#ifdef ENABLE_WALLET
    /// 8. URI IPC sending
    // - Do this early as we don't want to bother initializing if we are just calling IPC
    // - Do this *after* setting up the data directory, as the data directory hash is used in the name
    // of the server.
    // - Do this after creating app and setting up translations, so errors are
    // translated properly.
    if (PaymentServer::ipcSendCommandLine())
        exit(0);

    // Start up the payment server early, too, so impatient users that click on
    // girauno: links repeatedly have their payment requests routed to this process:
    app.createPaymentServer();
#endif

    /// 9. Main GUI initialization
    // Install global event filter that makes sure that long tooltips can be word-wrapped
    app.installEventFilter(new GUIUtil::ToolTipToRichTextFilter(TOOLTIP_WRAP_THRESHOLD, &app));
#if QT_VERSION < 0x050000
    // Install qDebug() message handler to route to debug.log
    qInstallMsgHandler(DebugMessageHandler);
#else
#if defined(Q_OS_WIN)
    // Install global event filter for processing Windows session related Windows messages (WM_QUERYENDSESSION and WM_ENDSESSION)
    qApp->installNativeEventFilter(new WinShutdownMonitor());
#endif
    // Install qDebug() message handler to route to debug.log
    qInstallMessageHandler(DebugMessageHandler);
#endif
    // Load GUI settings from QSettings
    app.createOptionsModel();

    // Subscribe to global signals from core
    uiInterface.InitMessage.connect(InitMessage);

    if (GetBoolArg("-splash", true) && !GetBoolArg("-min", false))
        app.createSplashScreen(isaTestNet);

    try
    {
        app.createWindow(isaTestNet);
        app.requestInitialize();
#if defined(Q_OS_WIN) && QT_VERSION >= 0x050000
        WinShutdownMonitor::registerShutdownBlockReason(QObject::tr("Girauno Core didn't yet exit safely..."), (HWND)app.getMainWinId());
#endif
        app.exec();
        app.requestShutdown();
        app.exec();
    } catch (std::exception& e) {
        PrintExceptionContinue(&e, "Runaway exception");
        app.handleRunawayException(QString::fromStdString(strMiscWarning));
    } catch (...) {
        PrintExceptionContinue(NULL, "Runaway exception");
        app.handleRunawayException(QString::fromStdString(strMiscWarning));
    }
    return app.getReturnValue();
}
#endif // GIRAUNO_QT_TEST
