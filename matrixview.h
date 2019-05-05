#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H


#include <QObject>
#include "automata.h"
#include <QPainter>

class Matrixview : public QObject
{
    Q_OBJECT

public:
    explicit Matrixview(QObject *parent = nullptr );
    void update(Automata* );
    QVector<struct State> cells() const;
    bool setCellAt(int index, const struct State &cell);

signals:
    void preCellAppended();
    void postCellAppended();

    void preCellRemoved(unsigned int index);
    void postCellRemoved();

public slots:
    void appendCell(struct State);
    void removeCell(unsigned int index);

 private:
    QVector<struct State> listOfState;
};

#endif // MATRIXVIEW_H
