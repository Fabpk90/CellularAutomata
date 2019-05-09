#include "matrixview.h"
#include <iostream>
#include<QVector>
#include<QTimer>
#include <math.h>
#include <windows.h>
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

   // connect(this,SIGNAL(listOfStateChanged()),this,SLOT(update));
    listOfState.append({QColor("green"), "State"});
    listOfState.append({QColor("blue"), "State"});
    for(int i=0;i<2498;i++){
        listOfState.append({QColor("yellow"),"State "+to_string(i)});

    }

    srand(time(NULL));
    this->timer=new QTimer();
    this->timer->connect(timer, SIGNAL(timeout()),this,SLOT(update()));

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
    if(cell.color == oldCell.color && cell.name == oldCell.name)
     return false;
    listOfState[index]=cell;
    /*listOfState[index].color= cell.color;
    listOfState[index].name=cell.name;
*/
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
    QColor test[5]; test[0]=QColor("blue");test[1]=QColor("green");test[2]=QColor("orange");test[3]=QColor("green");test[4]=QColor("blue");
    cout<<listOfState.size()<<endl;

   struct State s={QColor("orange"),to_string(1)};
//   for(int k=0;k<10;k++){

  /*     for(int i=0;i<2500;i++){
      removeCell(0);
   }
       for(int i=0;i<2500;i++){
       appendCell({test[rand()%5],to_string(1)});


   }*/
   for(int i=0;i<2500;i++)
   this->setCellAt(i,{test[rand()%5],to_string(1)});
   cout<<listOfState.size()<<endl;
    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);
    }
//}

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

void Matrixview::play(){

    this->timer->start(500);


}

void Matrixview::pause()
{
 this->timer->stop();

}

