include $(top_srcdir)/src/Makefile.include

AM_CPPFLAGS += -I$(top_srcdir)/src \
  -I$(top_builddir)/src/qt \
  -I$(top_builddir)/src/qt/forms \
  $(PROTOBUF_CFLAGS) \
  $(QR_CFLAGS)
bin_PROGRAMS = girauno-qt
noinst_LIBRARIES = libgiraunoqt.a
SUBDIRS = . $(BUILD_TEST_QT)
DIST_SUBDIRS = . test

# girauno qt core #
QT_TS = \
  locale/girauno_ach.ts \
  locale/girauno_af_ZA.ts \
  locale/girauno_ar.ts \
  locale/girauno_be_BY.ts \
  locale/girauno_bg.ts \
  locale/girauno_bs.ts \
  locale/girauno_ca_ES.ts \
  locale/girauno_ca.ts \
  locale/girauno_ca@valencia.ts \
  locale/girauno_cmn.ts \
  locale/girauno_cs.ts \
  locale/girauno_cy.ts \
  locale/girauno_da.ts \
  locale/girauno_de.ts \
  locale/girauno_el_GR.ts \
  locale/girauno_en.ts \
  locale/girauno_eo.ts \
  locale/girauno_es_CL.ts \
  locale/girauno_es_DO.ts \
  locale/girauno_es_MX.ts \
  locale/girauno_es.ts \
  locale/girauno_es_UY.ts \
  locale/girauno_et.ts \
  locale/girauno_eu_ES.ts \
  locale/girauno_fa_IR.ts \
  locale/girauno_fa.ts \
  locale/girauno_fi.ts \
  locale/girauno_fr_CA.ts \
  locale/girauno_fr.ts \
  locale/girauno_gl.ts \
  locale/girauno_gu_IN.ts \
  locale/girauno_he.ts \
  locale/girauno_hi_IN.ts \
  locale/girauno_hr.ts \
  locale/girauno_hu.ts \
  locale/girauno_id_ID.ts \
  locale/girauno_it.ts \
  locale/girauno_ja.ts \
  locale/girauno_ka.ts \
  locale/girauno_kk_KZ.ts \
  locale/girauno_ko_KR.ts \
  locale/girauno_ky.ts \
  locale/girauno_la.ts \
  locale/girauno_lt.ts \
  locale/girauno_lv_LV.ts \
  locale/girauno_mn.ts \
  locale/girauno_ms_MY.ts \
  locale/girauno_nb.ts \
  locale/girauno_nl.ts \
  locale/girauno_pam.ts \
  locale/girauno_pl.ts \
  locale/girauno_pt_BR.ts \
  locale/girauno_pt_PT.ts \
  locale/girauno_ro_RO.ts \
  locale/girauno_ru.ts \
  locale/girauno_sah.ts \
  locale/girauno_sk.ts \
  locale/girauno_sl_SI.ts \
  locale/girauno_sq.ts \
  locale/girauno_sr.ts \
  locale/girauno_sv.ts \
  locale/girauno_th_TH.ts \
  locale/girauno_tr.ts \
  locale/girauno_uk.ts \
  locale/girauno_ur_PK.ts \
  locale/girauno_uz@Cyrl.ts \
  locale/girauno_vi.ts \
  locale/girauno_vi_VN.ts \
  locale/girauno_zh_CN.ts \
  locale/girauno_zh_HK.ts \
  locale/girauno_zh_TW.ts

QT_FORMS_UI = \
  forms/aboutdialog.ui \
  forms/addressbookpage.ui \
  forms/askpassphrasedialog.ui \
  forms/coincontroldialog.ui \
  forms/editaddressdialog.ui \
  forms/helpmessagedialog.ui \
  forms/intro.ui \
  forms/openuridialog.ui \
  forms/optionsdialog.ui \
  forms/overviewpage.ui \
  forms/receivecoinsdialog.ui \
  forms/receiverequestdialog.ui \
  forms/rpcconsole.ui \
  forms/sendcoinsdialog.ui \
  forms/sendcoinsentry.ui \
  forms/signverifymessagedialog.ui \
  forms/transactiondescdialog.ui

QT_MOC_CPP = \
  moc_addressbookpage.cpp \
  moc_addresstablemodel.cpp \
  moc_askpassphrasedialog.cpp \
  moc_giraunoaddressvalidator.cpp \
  moc_giraunoamountfield.cpp \
  moc_giraunogui.cpp \
  moc_giraunounits.cpp \
  moc_clientmodel.cpp \
  moc_coincontroldialog.cpp \
  moc_coincontroltreewidget.cpp \
  moc_csvmodelwriter.cpp \
  moc_editaddressdialog.cpp \
  moc_guiutil.cpp \
  moc_intro.cpp \
  moc_macdockiconhandler.cpp \
  moc_macnotificationhandler.cpp \
  moc_monitoreddatamapper.cpp \
  moc_notificator.cpp \
  moc_openuridialog.cpp \
  moc_optionsdialog.cpp \
  moc_optionsmodel.cpp \
  moc_overviewpage.cpp \
  moc_paymentserver.cpp \
  moc_qvalidatedlineedit.cpp \
  moc_qvaluecombobox.cpp \
  moc_receivecoinsdialog.cpp \
  moc_receiverequestdialog.cpp \
  moc_recentrequeststablemodel.cpp \
  moc_rpcconsole.cpp \
  moc_sendcoinsdialog.cpp \
  moc_sendcoinsentry.cpp \
  moc_signverifymessagedialog.cpp \
  moc_splashscreen.cpp \
  moc_trafficgraphwidget.cpp \
  moc_transactiondesc.cpp \
  moc_transactiondescdialog.cpp \
  moc_transactionfilterproxy.cpp \
  moc_transactiontablemodel.cpp \
  moc_transactionview.cpp \
  moc_utilitydialog.cpp \
  moc_walletframe.cpp \
  moc_walletmodel.cpp \
  moc_walletview.cpp

GIRAUNO_MM = \
  macdockiconhandler.mm \
  macnotificationhandler.mm

QT_MOC = \
  girauno.moc \
  intro.moc \
  overviewpage.moc \
  rpcconsole.moc

QT_QRC_CPP = qrc_girauno.cpp
QT_QRC = girauno.qrc

PROTOBUF_CC = paymentrequest.pb.cc
PROTOBUF_H = paymentrequest.pb.h
PROTOBUF_PROTO = paymentrequest.proto

GIRAUNO_QT_H = \
  addressbookpage.h \
  addresstablemodel.h \
  askpassphrasedialog.h \
  giraunoaddressvalidator.h \
  giraunoamountfield.h \
  giraunogui.h \
  giraunounits.h \
  clientmodel.h \
  coincontroldialog.h \
  coincontroltreewidget.h \
  csvmodelwriter.h \
  editaddressdialog.h \
  guiconstants.h \
  guiutil.h \
  intro.h \
  macdockiconhandler.h \
  macnotificationhandler.h \
  monitoreddatamapper.h \
  notificator.h \
  openuridialog.h \
  optionsdialog.h \
  optionsmodel.h \
  overviewpage.h \
  paymentrequestplus.h \
  paymentserver.h \
  qvalidatedlineedit.h \
  qvaluecombobox.h \
  receivecoinsdialog.h \
  receiverequestdialog.h \
  recentrequeststablemodel.h \
  rpcconsole.h \
  sendcoinsdialog.h \
  sendcoinsentry.h \
  signverifymessagedialog.h \
  splashscreen.h \
  trafficgraphwidget.h \
  transactiondesc.h \
  transactiondescdialog.h \
  transactionfilterproxy.h \
  transactionrecord.h \
  transactiontablemodel.h \
  transactionview.h \
  utilitydialog.h \
  walletframe.h \
  walletmodel.h \
  walletmodeltransaction.h \
  walletview.h \
  winshutdownmonitor.h

RES_ICONS = \
  res/icons/add.png \
  res/icons/address-book.png \
  res/icons/girauno.ico \
  res/icons/girauno.png \
  res/icons/girauno_testnet.ico \
  res/icons/girauno_testnet.png \
  res/icons/clock1.png \
  res/icons/clock2.png \
  res/icons/clock3.png \
  res/icons/clock4.png \
  res/icons/clock5.png \
  res/icons/configure.png \
  res/icons/connect0_16.png \
  res/icons/connect1_16.png \
  res/icons/connect2_16.png \
  res/icons/connect3_16.png \
  res/icons/connect4_16.png \
  res/icons/debugwindow.png \
  res/icons/edit.png \
  res/icons/editcopy.png \
  res/icons/editpaste.png \
  res/icons/export.png \
  res/icons/filesave.png \
  res/icons/history.png \
  res/icons/key.png \
  res/icons/lock_closed.png \
  res/icons/lock_open.png \
  res/icons/overview.png \
  res/icons/qrcode.png \
  res/icons/quit.png \
  res/icons/receive.png \
  res/icons/remove.png \
  res/icons/send.png \
  res/icons/synced.png \
  res/icons/toolbar.png \
  res/icons/toolbar_testnet.png \
  res/icons/transaction0.png \
  res/icons/transaction2.png \
  res/icons/transaction_conflicted.png \
  res/icons/tx_inout.png \
  res/icons/tx_input.png \
  res/icons/tx_output.png \
  res/icons/tx_mined.png

GIRAUNO_QT_CPP = \
  girauno.cpp \
  giraunoaddressvalidator.cpp \
  giraunoamountfield.cpp \
  giraunogui.cpp \
  giraunounits.cpp \
  clientmodel.cpp \
  csvmodelwriter.cpp \
  guiutil.cpp \
  intro.cpp \
  monitoreddatamapper.cpp \
  notificator.cpp \
  optionsdialog.cpp \
  optionsmodel.cpp \
  qvalidatedlineedit.cpp \
  qvaluecombobox.cpp \
  rpcconsole.cpp \
  splashscreen.cpp \
  trafficgraphwidget.cpp \
  utilitydialog.cpp \
  winshutdownmonitor.cpp

if ENABLE_WALLET
GIRAUNO_QT_CPP += \
  addressbookpage.cpp \
  addresstablemodel.cpp \
  askpassphrasedialog.cpp \
  coincontroldialog.cpp \
  coincontroltreewidget.cpp \
  editaddressdialog.cpp \
  openuridialog.cpp \
  overviewpage.cpp \
  paymentrequestplus.cpp \
  paymentserver.cpp \
  receivecoinsdialog.cpp \
  receiverequestdialog.cpp \
  recentrequeststablemodel.cpp \
  sendcoinsdialog.cpp \
  sendcoinsentry.cpp \
  signverifymessagedialog.cpp \
  transactiondesc.cpp \
  transactiondescdialog.cpp \
  transactionfilterproxy.cpp \
  transactionrecord.cpp \
  transactiontablemodel.cpp \
  transactionview.cpp \
  walletframe.cpp \
  walletmodel.cpp \
  walletmodeltransaction.cpp \
  walletview.cpp
endif

RES_IMAGES = \
  res/images/about.png \
  res/images/splash.png \
  res/images/splash_testnet.png

RES_MOVIES = $(wildcard res/movies/spinner-*.png)

GIRAUNO_RC = res/girauno-qt-res.rc

libgiraunoqt_a_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms $(QT_DBUS_INCLUDES)
libgiraunoqt_a_SOURCES = $(GIRAUNO_QT_CPP) $(GIRAUNO_QT_H) $(QT_FORMS_UI) \
  $(QT_QRC) $(QT_TS) $(PROTOBUF_PROTO) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES)

nodist_libgiraunoqt_a_SOURCES = $(QT_MOC_CPP) $(QT_MOC) $(PROTOBUF_CC) \
  $(PROTOBUF_H) $(QT_QRC_CPP)

BUILT_SOURCES = $(nodist_libgiraunoqt_a_SOURCES)

#Generating these with a half-written protobuf header leads to wacky results.
#This makes sure it's done.
$(QT_MOC): $(PROTOBUF_H)
$(QT_MOC_CPP): $(PROTOBUF_H)

# girauno-qt binary #
girauno_qt_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms
girauno_qt_SOURCES = girauno.cpp
if TARGET_DARWIN
  girauno_qt_SOURCES += $(GIRAUNO_MM)
endif
if TARGET_WINDOWS
  girauno_qt_SOURCES += $(GIRAUNO_RC)
endif
girauno_qt_LDADD = libgiraunoqt.a $(LIBGIRAUNO_SERVER)
if ENABLE_WALLET
girauno_qt_LDADD += $(LIBGIRAUNO_WALLET)
endif
girauno_qt_LDADD += $(LIBGIRAUNO_CLI) $(LIBGIRAUNO_COMMON) $(LIBLEVELDB) $(LIBMEMENV) \
  $(BOOST_LIBS) $(QT_LIBS) $(QT_DBUS_LIBS) $(QR_LIBS) $(PROTOBUF_LIBS) $(BDB_LIBS)
girauno_qt_LDFLAGS = $(QT_LDFLAGS)

# forms/foo.h -> forms/ui_foo.h
QT_FORMS_H=$(join $(dir $(QT_FORMS_UI)),$(addprefix ui_, $(notdir $(QT_FORMS_UI:.ui=.h))))

#locale/foo.ts -> locale/foo.qm
QT_QM=$(QT_TS:.ts=.qm)

.PHONY: FORCE
.SECONDARY: $(QT_QM)

giraunostrings.cpp: FORCE
	$(MAKE) -C $(top_srcdir)/src qt/giraunostrings.cpp

translate: giraunostrings.cpp $(QT_FORMS_UI) $(QT_FORMS_UI) $(GIRAUNO_QT_CPP) $(GIRAUNO_QT_H) $(GIRAUNO_MM)
	@test -n $(LUPDATE) || echo "lupdate is required for updating translations"
	@QT_SELECT=$(QT_SELECT) $(LUPDATE) $^ -locations relative -no-obsolete -ts locale/girauno_en.ts

$(QT_QRC_CPP): $(QT_QRC) $(QT_QM) $(QT_FORMS_H) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES) $(PROTOBUF_H)
	@cd $(abs_srcdir); test -f $(RCC) && QT_SELECT=$(QT_SELECT) $(RCC) -name girauno -o $(abs_builddir)/$@ $< || \
	  echo error: could not build $@
	$(SED) -e '/^\*\*.*Created:/d' $@ > $@.n && mv $@{.n,}
	$(SED) -e '/^\*\*.*by:/d' $@  > $@.n && mv $@{.n,}

CLEANFILES = $(BUILT_SOURCES) $(QT_QM) $(QT_FORMS_H) *.gcda *.gcno
