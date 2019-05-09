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
  //  cout<<listOfState.size()<<endl;
    return (int)sqrt(listOfState.size());
}

Matrixview::Matrixview(QObject *parent) : QObject(parent)
{

    listOfState.append({QColor("green"), "State"});
    listOfState.append({QColor("blue"), "State"});
    for(int i=0;i<98;i++){
        listOfState.append({QColor("yellow"),"State "+to_string(i)});

    }
    //size=sqrt(listOfState.size());
}




QVector<State>& Matrixview::cells()
{
    return listOfState;
}

bool Matrixview::setCellAt(int index,const State& cell)
{
    if(index < 0 || index >= listOfState.size())
        return false;
    const struct State &oldCell= listOfState.at(index);
    if(cell.color == oldCell.color && cell.name == oldCell.name){
       cout<<"Pas entrée:i"<<endl; return false;}
    listOfState[index].color= cell.color;
    listOfState[index].name=cell.name;

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
    QColor test[5]; test[0]=QColor("blue");test[1]=QColor("green");test[2]=QColor("blue");test[3]=QColor("green");test[4]=QColor("blue");
    emit preClean(0,99);
   listOfState.resize(0);
    emit postCellRemoved();
   struct State s={QColor("orange"),to_string(1)};
   for(int k=0;k<10;k++){


       for(int i=0;i<100;i++){
       appendCell({test[k%5],to_string(1)});
    //this->setCellAt(i,{test[i%5],to_string(1)});

   }
    cout<<listOfState.size()<<endl;
   // engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);
    }
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

void Matrixview::setListOfState(const QVector<State> &value)
{
    listOfState = value;
}
