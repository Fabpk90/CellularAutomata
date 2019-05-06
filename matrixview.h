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
    Automata *automata;
    QQmlApplicationEngine* engine;
public:
    explicit Matrixview(QObject *parent = nullptr );
    void update(Automata* );
    QVector<struct State> cells() const;
    bool setCellAt(int index, const struct State &cell);

    Automata *getAutomata() const;
    void setAutomata(Automata *value);
    QQmlApplicationEngine *getEngine() const;
    void setEngine(QQmlApplicationEngine *value);

signals:
    void preCellAppended();
    void postCellAppended();

    void preCellRemoved(unsigned int index);
    void postCellRemoved();


public slots:
    void appendCell(struct State);
    void removeCell(unsigned int index);
    void update();
 private:
    QVector<struct State> listOfState;
};

#endif // MATRIXVIEW_H
