#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <iostream>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "matrixview.h"
#include "parser.h"
#include "filemanager.h"
#include "simulator.h"
//TODO ALL THE INPUT TESTS
class Interface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString probability READ probability WRITE setProbability NOTIFY probabilityChanged) //TODO input has to be int
    Q_PROPERTY(QString computeProbability READ computeProbability WRITE setComputeProbability NOTIFY computeProbabilityChanged) //TODO input has to be int
    Q_PROPERTY(QString posAndCount READ posAndCount WRITE setPosAndCount NOTIFY posAndCountChanged)
    Q_PROPERTY(QString stateToChangeTo READ stateToChangeTo WRITE setStateToChangeTo NOTIFY stateToChangeToChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(QString neighborhood READ neighborhood WRITE setNeighborhood NOTIFY neighborhoodChanged)
    Q_PROPERTY(QString maxGenerationsToSimulate READ maxGenerationsToSimulate WRITE setMaxGenerationsToSimulate NOTIFY maxGenerationsToSimulateChanged)
    Q_PROPERTY(QString sizeX READ sizeX WRITE setSizeX NOTIFY sizeXChanged)
    Q_PROPERTY(QString sizeY READ sizeY WRITE setSizeY NOTIFY sizeYChanged)

private:
    QString m_probability;
    QString m_computeProbability;
    QString m_posAndCount;
    QString m_stateToChangeTo;
    QString m_type;
    QString m_dimension;
    QString m_neighborhood;
    QString m_maxGenerationsToSimulate;
    QString m_sizeX;
    QString m_sizeY;
    QQmlApplicationEngine* engine;

    Parser parser;

public:
    explicit Interface(QObject *parent = nullptr);

    //init
    void initialiseParser(); //TODO
    QQmlApplicationEngine *getEngine() const;
    void setEngine(QQmlApplicationEngine *value);

    //probability
    QString probability() const
    {
        return m_probability;
    }
    Q_INVOKABLE void printProbability(); //for tests

    QString type() const
    {
        return m_type;
    }

    QString dimension() const
    {
        return m_dimension;
    }
    Q_INVOKABLE void printDimension(); //for tests

    QString neighborhood() const
    {
        return m_neighborhood;
    }

    QString maxGenerationsToSimulate() const
    {
        return m_maxGenerationsToSimulate;
    }
    Q_INVOKABLE void printMaxGenerationsToSimulate(); //for test

    QString sizeX() const
    {
        return m_sizeX;
    }

    QString sizeY() const
    {
        return m_sizeY;
    }
    /*Gestion de fichier*/
    Q_INVOKABLE void callSaveMatrix(string path, string name, string firstGen, string lastGen);//Demande pour sauvegarder un automate
    Q_INVOKABLE void callLoad(string name, string path);//Demande pour charger un automate

    /*Fenêtre de création d'automate*/
    /*Set type, dimension, voisinage , ceci est nécessaire pour l'interpréteur.*/
    void SendMandatoryInfo(); //TODO

    /*Fait appel à une série de fonctions de l'interpréteur.*/
    void OkCreateAutomata(); //TODO

    /*Nombre de dimensions de l'automate: Une dimension ou deux dimensions.*/
    void CallSetDim(QString dimension);

    /*Définit le voisinage de l'automate (Moore ou Von Neumann).*/
    void CallSetNeighborhood(QString neighborhood);

    /*Définit si l'automate sera de type stochastique ou déterministe.*/
    void CallType(QString type);

    /*Change le nombre de générations à simuler.*/
    void CallMaxGenerationsToSimulate(QString maxGenerationsToSimulate);

    /*Définit la taille de la matrice d'affichage.*/
    void CallMatrixSize(int x, int y);

    /*Appel la fonction de lecture de l'automate*/
    Q_INVOKABLE void callExecution();
    /*Retourne la dimension x de l'automate*/
    Q_INVOKABLE unsigned int getSizeX();
    /*Retourne la dimension y de l'automate*/
    Q_INVOKABLE unsigned int getSizeY();


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

    /*Fenêtre de création d'états */
   Q_INVOKABLE void CallSetStateName(QString probability);
    void CallSetColor(QString color);
   Q_INVOKABLE void OkCreateState(QString state);



signals:

    void probabilityChanged(QString probability);

    void computeProbabilityChanged(QString computeProbability);

    void posAndCountChanged(QString posAndCount);

    void stateToChangeToChanged(QString stateToChangeTo);

    void typeChanged(QString type);

    void dimensionChanged(QString dimension);

    void neighborhoodChanged(QString neighborhood);

    void maxGenerationsToSimulateChanged(QString maxGenerationsToSimulate);

    void sizeXChanged(QString sizeX);

    void sizeYChanged(QString sizeY);

public slots:
void setComputeProbability(QString computeProbability);
void setProbability(QString probability);
void setPosAndCount(QString posAndCount);
void setStateToChangeTo(QString stateToChangeTo);
void setDimension(QString dimension);
void setType(QString type);
void setNeighborhood(QString neighborhood);
void setMaxGenerationsToSimulate(QString maxGenerationsToSimulate);
void setSizeX(QString sizeX);
void setSizeY(QString sizeY);

};

#endif // INTERFACE_H
