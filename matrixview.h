#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H


#include <QObject>
#include "automata.h"
#include <QPainter>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class Matrixview : public QObject
{
    Q_OBJECT

public:
    explicit Matrixview(QObject *parent = nullptr );
    QVector<struct State>& cells();
    bool setCellAt(int index, const struct State& cell);

    Automata *getAutomata() const;
    void setAutomata(Automata *value);
    QQmlApplicationEngine *getEngine() const;
    void setEngine(QQmlApplicationEngine *value);
    Q_INVOKABLE int returnSize();
    void setListOfState(const QVector<State> &value);

signals:
    void preCellAppended();
    void postCellAppended();

    void preCellRemoved(unsigned int index);
    void postCellRemoved();
    void preCellUpdated(int index,int endIndex);
    void postCellUpdated();
    void preClean(int index, int endIndex);
    void listOfStateChanged();

public slots:
    void appendCell(struct State);
    void removeCell(unsigned int index);
    void update();
    void forward();
    void backward();
    void play();
    void pause();
 private:
    Automata *automata;
    QQmlApplicationEngine* engine;
    QVector<struct State> listOfState;
    QTimer * timer; //temporary thread. We will see how we manage it

};

#endif // MATRIXVIEW_H
