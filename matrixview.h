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
 //   Q_PROPERTY(double size READ getSize CONSTANT)
public:
    explicit Matrixview(QObject *parent = nullptr );
    void update(Automata* );
    QVector<struct State> cells() const;
    bool setCellAt(int index, const struct State &cell);

    Automata *getAutomata() const;
    void setAutomata(Automata *value);
    QQmlApplicationEngine *getEngine() const;
    void setEngine(QQmlApplicationEngine *value);
    //double getSize();
    Q_INVOKABLE int returnSize();
signals:
    void preCellAppended();
    void postCellAppended();

    void preCellRemoved(unsigned int index);
    void postCellRemoved();


public slots:
    void appendCell(struct State);
    void removeCell(unsigned int index);
    void update();
    void forward();
    void backward();
 private:
    Automata *automata;
    QQmlApplicationEngine* engine;
    QVector<struct State> listOfState;
   // double size;
};

#endif // MATRIXVIEW_H
