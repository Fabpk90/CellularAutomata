#include "matrixview.h"
#include <iostream>
#include<QVector>
#include <math.h>
Automata *Matrixview::getAutomata() const
{
    return automata;
}

void Matrixview::setAutomata(Automata *value)
{
    automata = value;
}

QQmlApplicationEngine *Matrixview::getEngine() const
{
    return engine;
}

void Matrixview::setEngine(QQmlApplicationEngine *value)
{
    engine = value;
}
/*
double Matrixview::getSize()
{
    return size;
}
*/
int Matrixview::returnSize()
{
    cout<<listOfState.size()<<endl;
    return (int)sqrt(listOfState.size());
}

Matrixview::Matrixview(QObject *parent) : QObject(parent)
{

    listOfState.append({QColor("green"), "State"});
    listOfState.append({QColor("blue"), "State"});
    for(int i=0;i<9998;i++){
        listOfState.append({QColor("yellow"),"State "+to_string(i)});

    }
    //size=sqrt(listOfState.size());
}




QVector<State> Matrixview::cells() const
{
    return listOfState;
}

bool Matrixview::setCellAt(int index, const State& cell)
{
    if(index < 0 || index >= listOfState.size())
        return false;
    const struct State &oldCell= listOfState.at(index);
    if(cell.color == oldCell.color && cell.name == oldCell.name)
        return false;
    listOfState[index]= cell;
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

void Matrixview::update()//temporaire en attendant l'implémentation
{

   for(int i=0;i<100;i++){

    this->setCellAt(i,{QColor("orange"),to_string(i)});

   }
   engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);

}

void Matrixview::forward()
{
    automata->NextGen();

    for(int i=0; i<automata->GetSizeX();i++){

        for (int j=0; j<automata->GetSizeY(); j++) {
            this->setCellAt(i*10+j,automata->GetCellState(i,j));

        }

    }

    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);

}

void Matrixview::backward()
{
    automata->PreviousGen();
    for(int i=0; i<automata->GetSizeX();i++){

        for (int j=0; j<automata->GetSizeY(); j++) {
            this->setCellAt(i*10+j,automata->GetCellState(i,j));

        }

    }
    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"),this);
}
