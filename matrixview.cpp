#include "matrixview.h"

Matrixview::Matrixview(QObject *parent) : QObject(parent)
{

}



void Matrixview::update(Automata* a){

    for(unsigned int i=0;i< a->GetStates().size();i++){

        this->setCellAt(i,a->GetStates()[i]);

    }


}

QVector<State> Matrixview::cells() const
{
    return listOfState;
}

bool Matrixview::setCellAt(int index, const State &cell)
{
    if(index < 0 || index >= listOfState.size())
        return false;
    const struct State &oldCell= listOfState.at(index);
    if(cell.color == oldCell.color && cell.name == oldCell.name)
        return false;
    listOfState[index] =cell;
    return true;

}

void Matrixview::appendCell(struct State cell)
{
    emit preCellAppended();

    listOfState.append(cell);
    emit postCellAppended();
}

void Matrixview::removeCell(unsigned int index)
{
    emit preCellRemoved(index);
    listOfState.remove(index);
    emit postCellRemoved();


}
