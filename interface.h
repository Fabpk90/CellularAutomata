#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <iostream>

class Interface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString probability READ probability WRITE setProbability NOTIFY probabilityChanged)
private:
    QString m_probability;
    QString dimension;
    QString type;
    QString neighborhood;

public:
    explicit Interface(QObject *parent = nullptr);

    //probability
    QString probability() const
    {
        return m_probability;
    }
    void setProbability(const QString &probability);
    Q_INVOKABLE void printProbability(); //for tests

    /*Fenêtre de création d'automate*/
            void SendMandatoryInfo();
            /*Set type, dimension, voisinage , ceci est nécessaire pour l'interpréteur.*/

            void OkCreateAutomata();
            /*Fait appel à une série de fonctions de l'interpréteur.*/

            void CallSetDim(const QString &dimension);
            /*Nombre de dimensions de l'automate: Une dimension ou deux dimensions.*/

            void CallSetNeighborhood(const QString &neighborhood);
            /*Définit le voisinage de l'automate (Moore ou Von Neumann).*/

            void CallType(const QString &type);
            /*Définit si l'automate sera de type stochastique ou déterministe.*/

            void CallMaxGenerationsToSimulate(QString maxGenerationsToSimulate);
            /*Change le nombre de générations à simuler.*/

            void CallMatrixSize(int x, int y);
            /*Définit la taille de la matrice d'affichage.*/



signals:

    void probabilityChanged(QString probability);

public slots:
};

#endif // INTERFACE_H
