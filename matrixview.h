#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H


#include <QObject>
#include "automata.h"
#include "parser.h"
#include <QPainter>
#include <QQmlApplicationEngine>
#include <QQmlContext>

class Matrixview : public QObject
{
    Q_OBJECT

public:
    explicit Matrixview(QObject *parent = nullptr );
    QVector<struct State>& cells();//liste des cellules à afficher
    bool setCellAt(int index, const struct State& cell);

    Parser *getParser() const;
    void setParser(Parser *value);
    QQmlApplicationEngine *getEngine() const;
    void setEngine(QQmlApplicationEngine *value);
    Q_INVOKABLE int returnSize();
    void setListOfState(const QVector<State> &value);

    void emptyMatrix();
    void selectGen(int gen);

signals:
    void preCellAppended();// signaux avant et après ajout de cellule
    void postCellAppended();
    void preCellRemoved(unsigned int index);//signaux avant et après suppression
    void postCellRemoved();


public slots:
    void appendCell(struct State);
    void removeCell(unsigned int index);
    void update();
    void forward();
    void backward();
    void play();
    void pause();
    void sizeMatrix(QString H, QString W);
    void initMatrix();

 private:
    Parser* parser;
    QQmlApplicationEngine* engine;
    QVector<struct State> listOfState;
    QTimer * timer; //temporary thread. We will see how we manage it

};

#endif // MATRIXVIEW_H
