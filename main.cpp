#include <iostream>
#include "automata.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "interface.h"
#include "matrixmodel.h"
#include "matrixview.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Some Company"); app.setOrganizationDomain("somecompany.com"); app.setApplicationName("Amazing Application");
    qmlRegisterType<Interface>("Interface",1,0,"Interface");
    qmlRegisterType<MatrixModel>("Interface",1,0,"MatrixModel");
    qmlRegisterUncreatableType <Matrixview> ("Interface",1,0, "Matrixview",QStringLiteral("Avoid creating Matrixview in qml"));
    Matrixview matrix;
    Interface interface;
    QQmlApplicationEngine engine;
    interface.setEngine(&engine);
    matrix.setEngine(&engine) ;
    engine.rootContext()->setContextProperty(QStringLiteral("matrixview"), &matrix);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    Automata ca;

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
