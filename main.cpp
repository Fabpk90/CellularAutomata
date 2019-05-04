#include <iostream>
#include "automata.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "interface.h"
#include "parser.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<Interface>("Interface",1,0,"Interface");

    QQmlApplicationEngine engine;
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

    //prints an error, correct behavior
    //ca.RandomizeCurrentGen();

    State state;
    state.name = "Yeppa";
    state.color = QColor(50, 20, 10);
    ca.AddState(state);
    state.name = "Yo";
    ca.AddState(state);

    Generation g;
    g.generationID = 10;
    ca.AddGeneration(g);
    g.generationID = 20;
    ca.AddGeneration(g);
    g.generationID = 30;
    ca.AddGeneration(g);

    cout << p.AutomataToString() << endl;
    cout << p.HistoryToString(1,3) << endl;

    //ca.RandomizeCurrentGen();

    return app.exec();
}
