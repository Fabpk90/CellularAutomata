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

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Some Company"); app.setOrganizationDomain("somecompany.com"); app.setApplicationName("Amazing Application");
    qmlRegisterType<Interface>("Interface",1,0,"Interface");
    qmlRegisterType<ListModel>("Interface", 1, 0, "ListModel");
    qmlRegisterUncreatableType<List>("Interface", 1, 0, "List",QStringLiteral("List should not be created in QML"));
    List stateListView;
    List ruleListView;
    qmlRegisterType<MatrixModel>("Interface",1,0,"MatrixModel");
    qmlRegisterUncreatableType <Matrixview> ("Interface",1,0, "Matrixview",QStringLiteral("Avoid creating Matrixview in qml"));
    Matrixview matrix;
    Interface interface;
    QQmlApplicationEngine engine;
    interface.setEngine(&engine);
    matrix.setEngine(&engine) ;
    stateListView.setEngine(&engine);
    ruleListView.setEngine(&engine);
    engine.rootContext()->setContextProperty(QStringLiteral("stateListView"), &stateListView);
    engine.rootContext()->setContextProperty(QStringLiteral("ruleListView"), &ruleListView);
    engine.rootContext()->setContextProperty(QStringLiteral("matrixview"), &matrix);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    Automata ca = Automata(true, true, 10, 20, vector<Rule*>()
                           , vector<State>(), vector<Generation>());

    Parser p;
    p.SetAutomata(&ca);

    Generation gen;
    gen.cellMatrix = vector<unsigned int>();
    unsigned int i = 0;
    while(i < 3){
        gen.generationID = i;
        i++;
        ca.AddGeneration(gen);
        //ca.RemoveGeneration(gen.generationID);
    }
    ca.ChooseGen(0);
    //ca.PreviousGen();
    ca.NextGen();

    State state;
    state.name = "Yeppa";
    state.color = QColor(50, 20, 10);
    ca.AddState(state);
    state.name = "Yo";
    ca.AddState(state);


    //cout << p.AutomataToString() << endl;
    cout << p.HistoryToString(0,14) << endl;

    //ca.RandomizeCurrentGen();
    return app.exec();
}
