#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H


#include <QObject>
#include "automata.h"
#include <QPainter>

class Matrixview : public QObject
{
    Q_OBJECT
    Automata *automata;
public:
    explicit Matrixview(QObject *parent = nullptr );
    void update(Automata* );
    QVector<struct State> cells() const;
    bool setCellAt(int index, const struct State &cell);

    Automata *getAutomata() const;
    void setAutomata(Automata *value);

signals:
    void preCellAppended();
    void postCellAppended();

    void preCellRemoved(unsigned int index);
    void postCellRemoved();
    void postUpdate();
    void preUpdate();

public slots:
    void appendCell(struct State);
    void removeCell(unsigned int index);
    void update();
 private:
    QVector<struct State> listOfState;
};

#endif // MATRIXVIEW_H
