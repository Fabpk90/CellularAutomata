#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <iostream>

//TODO ALL THE INPUT TESTS
class Interface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString probability READ probability WRITE setProbability NOTIFY probabilityChanged) //TODO input has to be int
    Q_PROPERTY(QString computeProbability READ computeProbability WRITE setComputeProbability NOTIFY computeProbabilityChanged) //TODO input has to be int
    Q_PROPERTY(QString posAndCount READ posAndCount WRITE setPosAndCount NOTIFY posAndCountChanged)
    Q_PROPERTY(QString stateToChangeTo READ stateToChangeTo WRITE setStateToChangeTo NOTIFY stateToChangeToChanged)

private:
    QString m_probability;
    QString dimension;
    QString type;
    QString neighborhood;
    QString m_computeProbability;
    QString m_posAndCount;
    QString m_stateToChangeTo;

public:
    explicit Interface(QObject *parent = nullptr);

    //init
    void initialiseParser(); //TODO

    //probability
    QString probability() const
    {
        return m_probability;
    }
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


    //computeProbability
    QString computeProbability() const
    {
        return m_computeProbability;
    }
    Q_INVOKABLE void printComputeProbability(); // for tests

    //posAndCount
    QString posAndCount() const
    {
        return m_posAndCount;
    }
    Q_INVOKABLE void printPosAndCount(); //for tests

    //stateToChangeTo
    QString stateToChangeTo() const
    {
        return m_stateToChangeTo;
    }
    Q_INVOKABLE void printStateToChangeTo(); //for tests

    void CallSetProbability(QString probability);//TODO
    void CallSetComputeProbability(QString computeProbability);//TODO
    void CallSetPosAndCount(QString posAndCount);//TODO
    void CallSetStateToChangeTo(QString stateToChangeTo);//TODO
    void CallGetStates(); //TODO
    Q_INVOKABLE void okCreateRule(); //TODO

signals:

    void probabilityChanged(QString probability);

    void computeProbabilityChanged(QString computeProbability);

    void posAndCountChanged(QString posAndCount);

    void stateToChangeToChanged(QString stateToChangeTo);

public slots:
void setComputeProbability(QString computeProbability);
void setProbability(QString probability);
void setPosAndCount(QString posAndCount);
void setStateToChangeTo(QString stateToChangeTo);
};

#endif // INTERFACE_H
