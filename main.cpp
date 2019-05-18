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
    QLocale::setDefault(QLocale::c());
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
    QQmlApplicationEngine engine;
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
    gen.cellMatrix.push_back(1);
    gen.cellMatrix.push_back(2);
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
    //cout << p.HistoryToString(0,3) << endl;

    //string test = "Position;1;0;8;(-1;1;0);(0;1;0);(1;1;0);(-1;0;0);(1;0;0);(-1;-1;0);(0;-1;0);(1;-1;0);99.9;";
    //p.ParseAndAddRules(&test);

    string yes = "yeppa";
    p.ParseFile(&yes);

    //ca.RandomizeCurrentGen();
    return app.exec();
}
