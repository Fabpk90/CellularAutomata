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

int Matrixview::returnSize()
{
    return (int)sqrt(listOfState.size());
}

Matrixview::Matrixview(QObject *parent) : QObject(parent)
{

   /*

        uint h= this.parser.getAutomata().getSizeX();
        uint l= this.parser.getAutomata().getSizeY();

        for(int i=0;i<h;i++){
            for(int j =0;j<l;j++){
               listOfState.append(this.parser.getAutomata().getCellState());

            }

        }



    */
    listOfState.append({QColor("green"), "State"});
    listOfState.append({QColor("blue"), "State"});

    for(int i=0;i<9998;i++){

        listOfState.append({QColor("yellow"),"State "+to_string(i)});

    }

    srand(time(NULL));
    this->timer=new QTimer();
    this->timer->connect(timer, SIGNAL(timeout()),this,SLOT(update()));

}




QVector<State>& Matrixview::cells()//retourne la liste représentant la matrice
{
    return listOfState;
}

bool Matrixview::setCellAt(int index,const State& cell)//change l'état d'une cellule à une position donnée
{
    if(index < 0 || index >= listOfState.size())
        return false;
    const struct State &oldCell= listOfState.at(index);
    if(cell.color == oldCell.color && cell.name == oldCell.name)
     return false;
    listOfState[index]=cell;
    return true;

}



void Matrixview::appendCell(struct State cell)//ajoute des cases dans la matrice d'affichage
{
    emit preCellAppended();

    listOfState.append(cell);
    emit postCellAppended();
}

void Matrixview::removeCell(unsigned int index)//retire des cases dans la mtrice d'affichage
{
    emit preCellRemoved(index);
    listOfState.remove(index);
    emit postCellRemoved();


}

void Matrixview::update()//Met à jour l'affichage de la matrice   /*temporaire en attendant l'implémentation*/
{
   /*
        uint h= this.parser.getAutomata().getSizeX();
        uint l= this.parser.getAutomata().getSizeY();

        for(int i=0;i<h;i++){
            for(int j =0;j<l;j++){
               setCellAt(i*10+j,this.parser.getAutomata().getCellState());

            }



    */


    QColor test[5]; test[0]=QColor("blue");test[1]=QColor("green");test[2]=QColor("orange");test[3]=QColor("green");test[4]=QColor("blue");
   struct State s={QColor("orange"),to_string(1)};

   for(int i=0;i<10000;i++)
   this->setCellAt(i,{test[rand()%5],to_string(1)});
    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);
    }



void Matrixview::forward()//permet d'avancer dans l'historique
{
    automata->NextGen();

    for(int i=0; i<automata->GetSizeX();i++){

        for (int j=0; j<automata->GetSizeY(); j++) {
            this->setCellAt(i*10+j,automata->GetCellState(i,j));

        }

    }

    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);


}

void Matrixview::backward()//permet de revenir en arrière dans l'historique
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


void Matrixview::play()//lance la simulation et l'affichage s'en suit
{
    //simulate();
    this->timer->start(500);


}

void Matrixview::pause()//met en pause l'éxcecution
{
    //pause du thread à ajouter ici
    this->timer->stop();

}

