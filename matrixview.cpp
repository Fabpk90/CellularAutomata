#include "matrixview.h"
#include <iostream>
#include<QVector>
#include<QTimer>
#include <math.h>

Parser *Matrixview::getParser() const
{
    return parser;
}

void Matrixview::setParser(Parser *value)
{
    parser = value;
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
    int a =sqrt(listOfState.size());
    cout<<"a:"<<a<<endl;
    return a;
}

Matrixview::Matrixview(QObject *parent) : QObject(parent)
{

        listOfState.append({QColor("white"),"State "+to_string(1)});



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

void Matrixview::update()//Met à jour l'affichage de la matrice
{
parser->GetAutomata()->Simulate();

int h =parser->GetAutomata()->GetSizeX();
int w =parser->GetAutomata()->GetSizeY();

for (int i =0;i<h;i++) {
    for (int j =0; j<w ;j++) {
        this->setCellAt(i*h+j, parser->GetAutomata()->GetCellState(i,j));

    }
}

engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);
}

void Matrixview::forward()//permet d'avancer dans l'historique
{
    this->timer->stop();
    if(parser != nullptr){
    parser->GetAutomata()->NextGen();

    int h =parser->GetAutomata()->GetSizeX();
    int w =parser->GetAutomata()->GetSizeY();

    for (int i =0;i<h;i++) {
        for (int j =0; j<w ;j++) {
            this->setCellAt(i*h+j, parser->GetAutomata()->GetCellState(i,j));

        }
    }

    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);
}

}

void Matrixview::backward()//permet de revenir en arrière dans l'historique
{
     this->timer->stop();
    if(parser != nullptr){
    parser->GetAutomata()->PreviousGen();
    int h =parser->GetAutomata()->GetSizeX();
    int w =parser->GetAutomata()->GetSizeY();

    for (int i =0;i<h;i++) {
        for (int j =0; j<w ;j++) {
            this->setCellAt(i*h+j, parser->GetAutomata()->GetCellState(i,j));

        }
    }

    engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);

    }
}
void Matrixview::setListOfState(const QVector<State> &value)
{
    listOfState = value;
}

void Matrixview::emptyMatrix()
{
    int size=listOfState.size();
    for (int i=0;i<size;i++) {
        removeCell(0);

    }

}

void Matrixview::selectGen(int gen)
{
    this->timer->stop();
   if(parser != nullptr){
    parser->GetAutomata()->ChooseGen(gen);
   int h =parser->GetAutomata()->GetSizeX();
   int w =parser->GetAutomata()->GetSizeY();

   for (int i =0;i<h;i++) {
       for (int j =0; j<w ;j++) {
           this->setCellAt(i*h+j, parser->GetAutomata()->GetCellState(i,j));

       }
   }

   engine->rootContext()->setContextProperty(QStringLiteral("matrixview"), this);

   }
}


void Matrixview::play()//lance la simulation et l'affichage s'en suit
{
   this->timer->start(500);
}

void Matrixview::pause()//met en pause l'éxcecution
{

    this->timer->stop();

}

void Matrixview::sizeMatrix(QString H,QString W)
{

    int size=listOfState.size();
    for (int i=0;i<size;i++) {
        removeCell(0);

    }

    int h=H.toInt();int w= W.toInt();
    for(int i=0;i<h;i++){

        for(int j=0;j<w;j++){

            appendCell({QColor("white"),to_string(i*10+j)});

        }


    }


}

void Matrixview::initMatrix()
{

    int size=listOfState.size();
    for (int i=0;i<size;i++) {
        removeCell(0);

    }
     if(parser !=nullptr){
    int h=parser->GetAutomata()->GetSizeX();int w=parser->GetAutomata()->GetSizeY();

    for(int i=0;i<h;i++){

        for(int j=0;j<w;j++){

             listOfState.append(parser->GetAutomata()->GetCellState(i,j));

        }


    }
   }

}

