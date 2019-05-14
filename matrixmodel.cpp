#include "matrixmodel.h"
#include "matrixview.h"
#include <iostream>

MatrixModel::MatrixModel(QObject *parent)
    : QAbstractListModel(parent),listOfState(nullptr)
{

}

int MatrixModel::rowCount(const QModelIndex &parent) const //renvoie la taille du vecteur représentant les éléments de la matrice de l'automate cellulaire
{

    if (parent.isValid() || !listOfState)
        return 0;

    return listOfState->cells().size();
}

QVariant MatrixModel::data(const QModelIndex &index, int role) const //fonction chargé de la création de données dans le modèle
{

    if (!index.isValid() || !listOfState)
        return QVariant();

    const State cell = this->listOfState->cells().at(index.row());
    switch(role){
    case Color:
        return cell.color;
    case StateName:
        return QString::fromStdString(cell.name);
    }
    return QVariant();
}

bool MatrixModel::setData(const QModelIndex &index, const QVariant &value, int role)//fonction appelée en cas de changement de donnée dans le qml
{
    if(!listOfState)
        return false;
   struct State cell =this->listOfState->cells().at(index.row());
   switch(role){
   case Color:
      value.value<QColor>();break;
   case StateName:
       cell.name = value.toString().toUtf8().constData();break;
   }

   if (listOfState->setCellAt(index.row(),cell)) {

       emit dataChanged(index, index, QVector<int>() << role);
       return true;
    }
    return false;
}

Qt::ItemFlags MatrixModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> MatrixModel::roleNames() const //permet de déclarer les objets de la liste comme ayant comme propriété une couleur et un nom
{
    QHash<int, QByteArray> states;
    states[Color]="color";
    states[StateName]="name";
    return states;

}

Matrixview *MatrixModel::getListOfState() const //renvoie la liste
{
    return listOfState;
}

void MatrixModel::setListOfState(Matrixview *value) // ajoute des colonnes ou en supprime dans l'affichage du modèle
{
    beginResetModel();
    if(listOfState)
        listOfState->disconnect();
    listOfState = value;

    if(listOfState){

        connect(listOfState, &Matrixview::preCellAppended, this ,[=](){
            const int index = listOfState->cells().size();
            beginInsertRows(QModelIndex(), index, index);

        });
        connect(listOfState, &Matrixview::postCellAppended, this ,[=](){
           endInsertRows();

        });
        connect(listOfState, &Matrixview::preCellRemoved, this ,[=](int index){
          beginRemoveRows(QModelIndex(), index, index);

        });

        connect(listOfState, &Matrixview::postCellRemoved, this ,[=](){
           endRemoveRows();

        });


    }
    endResetModel();

}
