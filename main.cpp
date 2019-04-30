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

    cout << p.AutomataToString() << " yep" << endl;


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

    //Automata::State state;
    //ca.AddState(state);
    //ca.AddState(state);

    //ca.RandomizeCurrentGen();

    return app.exec();




}
