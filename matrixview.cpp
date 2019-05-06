#include "matrixview.h"
#include <iostream>
Automata *Matrixview::getAutomata() const
{
    return automata;
}

void Matrixview::setAutomata(Automata *value)
{
    automata = value;
}

Matrixview::Matrixview(QObject *parent) : QObject(parent)
{

    listOfState.append({QColor("green"), "State"});
    listOfState.append({QColor("blue"), "State"});
    for(int i=0;i<98;i++){
        listOfState.append({QColor("yellow"),"State "+to_string(i)});

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
    cout<<"changes"<<endl;
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

void Matrixview::update()
{

    listOfState[1]={QColor("blue"), "try"};
   // for(int i=0;i<98;i++){
        //this->setCellAt(3,{QColor("orange"),to_string(3)});
        /*  emit preUpdate();
        listOfState.append({QColor("green"),to_string(i)});
        emit postUpdate();*/
    //}


}
