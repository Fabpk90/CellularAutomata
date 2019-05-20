#include <iostream>
#include "automata.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "interface.h"
#include "parser.h"
#include "matrixmodel.h"
#include "matrixview.h"
#include "listmodel.h"
#include "list.h"

int main(int argc, char *argv[])
{
    Interface myInterface;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QLocale::setDefault(QLocale::c());
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Some Company"); app.setOrganizationDomain("somecompany.com"); app.setApplicationName("Amazing Application");
    qmlRegisterType<Interface>("Interface",1,0,"Interface");
    qmlRegisterType<ListModel>("Interface", 1, 0, "ListModel");
    qmlRegisterUncreatableType<List>("Interface", 1, 0, "List",QStringLiteral("List should not be created in QML"));
    //List stateListView;
    //List ruleListView;
    qmlRegisterType<MatrixModel>("Interface",1,0,"MatrixModel");
    qmlRegisterUncreatableType <Matrixview> ("Interface",1,0, "Matrixview",QStringLiteral("Avoid creating Matrixview in qml"));
    Matrixview matrix;
    QQmlApplicationEngine engine;
    matrix.setEngine(&engine) ;
    myInterface.getStateListView()->setEngine(&engine);
    myInterface.getRuleListView()->setEngine(&engine);
    engine.rootContext()->setContextProperty(QStringLiteral("stateListView"), myInterface.getStateListView());
    engine.rootContext()->setContextProperty(QStringLiteral("ruleListView"), myInterface.getRuleListView());
    engine.rootContext()->setContextProperty(QStringLiteral("matrixview"), &matrix);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
