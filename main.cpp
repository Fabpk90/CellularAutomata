#include "automata.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    Automata ca;

    Automata::Generation gen;
    gen.cellMatrix = vector<unsigned int>();
    gen.generationID = 0;

    ca.AddGeneration(gen);
    ca.RemoveGeneration(gen.generationID);

    return app.exec();
}
