#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?req-dontexist="));
    QVERIFY(!GUIUtil::parseGiraunoURI(uri, &rv));

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?dontexist="));
    QVERIFY(GUIUtil::parseGiraunoURI(uri, &rv));
    QVERIFY(rv.address == QString("175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?label=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseGiraunoURI(uri, &rv));
    QVERIFY(rv.address == QString("175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W"));
    QVERIFY(rv.label == QString("Wikipedia Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?amount=0.001"));
    QVERIFY(GUIUtil::parseGiraunoURI(uri, &rv));
    QVERIFY(rv.address == QString("175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?amount=1.001"));
    QVERIFY(GUIUtil::parseGiraunoURI(uri, &rv));
    QVERIFY(rv.address == QString("175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?amount=100&label=Wikipedia Example"));
    QVERIFY(GUIUtil::parseGiraunoURI(uri, &rv));
    QVERIFY(rv.address == QString("175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Wikipedia Example"));

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseGiraunoURI(uri, &rv));
    QVERIFY(rv.address == QString("175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseGiraunoURI("girauno://175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?message=Wikipedia Example Address", &rv));
    QVERIFY(rv.address == QString("175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?req-message=Wikipedia Example Address"));
    QVERIFY(GUIUtil::parseGiraunoURI(uri, &rv));

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?amount=1,000&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseGiraunoURI(uri, &rv));

    uri.setUrl(QString("girauno:175tWpb8K1S7NmH4Zx6rewF9WQrcZv245W?amount=1,000.0&label=Wikipedia Example"));
    QVERIFY(!GUIUtil::parseGiraunoURI(uri, &rv));
}
