#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <iostream>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "matrixview.h"
#include "list.h"
#include "listmodel.h"
#include "parser.h"
#include "filemanager.h"
#include "simulator.h"

#define SIZEOFINDEXARRAYS 11

//TODO ALL THE INPUT TESTS
class Interface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString probability READ probability WRITE setProbability NOTIFY probabilityChanged)
    Q_PROPERTY(QString posAndCount READ posAndCount WRITE setPosAndCount NOTIFY posAndCountChanged)
    Q_PROPERTY(QString stateToChangeTo READ stateToChangeTo WRITE setStateToChangeTo NOTIFY stateToChangeToChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString dimension READ dimension WRITE setDimension NOTIFY dimensionChanged)
    Q_PROPERTY(QString neighborhood READ neighborhood WRITE setNeighborhood NOTIFY neighborhoodChanged)
    Q_PROPERTY(QString maxGenerationsToSimulate READ maxGenerationsToSimulate WRITE setMaxGenerationsToSimulate NOTIFY maxGenerationsToSimulateChanged)
    Q_PROPERTY(QString sizeX READ sizeX WRITE setSizeX NOTIFY sizeXChanged)
    Q_PROPERTY(QString sizeY READ sizeY WRITE setSizeY NOTIFY sizeYChanged)
    Q_PROPERTY(QString stateName READ stateName WRITE setStateName NOTIFY stateNameChanged)
    Q_PROPERTY(QString stateColor READ stateColor WRITE setStateColor NOTIFY stateColorChanged)
    Q_PROPERTY(QString numbState READ numbState WRITE setNumbState NOTIFY numbStateChanged)

private:
    QString m_probability;
    QString m_posAndCount;
    QString m_stateToChangeTo;
    QString m_type;
    QString m_dimension;
    QString m_neighborhood;
    QString m_maxGenerationsToSimulate;
    QString m_sizeX;
    QString m_sizeY;
    QString m_stateName;
    QString m_stateColor;
    QString m_numbState;
    string dataToParse;
    QQmlApplicationEngine* engine;
    Matrixview* matrixview;
    //Initialisation du premier Automate
    Automata* ca = nullptr;
    Parser parser;
    vector<int> stateVector;
    int rememberIndex;
    QString matrixIndexAndStateIndex[SIZEOFINDEXARRAYS]; //9 cas pour la matrice de creation et le 10eme pour le toChangeTo 11eme pour le compute probability
    QString posIndex[SIZEOFINDEXARRAYS];//idem
    List l;
    List stateListView;
    List ruleListView;

public:
    explicit Interface(QObject *parent = nullptr);
    //init
    Q_INVOKABLE void initialiseParser();
    Q_INVOKABLE void initMatrix();
    QQmlApplicationEngine *getEngine() const;
    void setEngine(QQmlApplicationEngine *value);
    List* getStateListView();
    List* getRuleListView();
    //probability
    QString probability() const;
    QString type() const;
    Q_INVOKABLE QString dimension() const;
    Q_INVOKABLE QString neighborhood() const;
    QString maxGenerationsToSimulate() const;
    QString sizeX() const;
    QString sizeY() const;

    /*Gestion de fichier*/
    Q_INVOKABLE void callSaveMatrix(QString path, QString name, QString firstGen=QString(""), QString lastGen=QString(""));//Demande pour sauvegarder un automate
    Q_INVOKABLE void callLoad(QString name, QString path);//Demande pour charger un automate

    /*Fenêtre de création d'automate*/
    /*Set type, dimension, voisinage , ceci est nécessaire pour l'interpréteur.*/
    Q_INVOKABLE void sendMandatoryInfo();

    /*Nombre de dimensions de l'automate: Une dimension ou deux dimensions.*/
    void CallSetDim();

    /*Définit le voisinage de l'automate (Moore ou Von Neumann).*/
    void CallSetNeighborhood();

    /*Définit si l'automate sera de type stochastique ou déterministe.*/
    void CallSetType();

    /*Change le nombre de générations à simuler.*/
    void CallMaxGenerationsToSimulate();

    /*Définit la taille de la matrice d'affichage.*/
    void CallMatrixSize();

    /*Appel la fonction de lecture de l'automate*/
    Q_INVOKABLE void callExecution();
    /*Retourne la dimension x de l'automate*/
   // Q_INVOKABLE unsigned int getSizeX();
    /*Retourne la dimension y de l'automate*/
   // Q_INVOKABLE unsigned int getSizeY();

    //posAndCount
    QString posAndCount() const;

    //stateToChangeTo
    QString stateToChangeTo() const;

    void CallSetProbability(QString probability);//TODO
    void CallSetPosAndCount(QString posAndCount);//TODO
    void CallSetStateToChangeTo(QString stateToChangeTo);//TODO
    void CallGetStates(); //TODO
    Q_INVOKABLE void okCreateRule();

    /*Fenêtre de création d'états */
    Q_INVOKABLE void CallSetStateName(QString probability);
    void CallSetColor(QString color);
    Q_INVOKABLE void okCreateState(QString state);
    Q_INVOKABLE void okCreateHistory();//crée la première génération (gen 0)


    QString stateName() const;
    Q_INVOKABLE QString getStateName();
    QString stateColor() const;
    Q_INVOKABLE QString getStateColor();
    Q_INVOKABLE int getRememberIndex() const;
    Q_INVOKABLE void setRememberIndex(int value);
    Q_INVOKABLE void associateStateAndIndex(QString StateIndex);
    Q_INVOKABLE void cleanRuleCreationWindow();
    Q_INVOKABLE void chooseGen(QString gen);
    Q_INVOKABLE void loadInterface();
    Q_INVOKABLE QString returnCurrentGen();
    Q_INVOKABLE void updateStateVector(int index,int stateId);
    Q_INVOKABLE void sizeTheVector();
    Q_INVOKABLE void displayEverything();
    Matrixview *getMatrixview() const;
    void setMatrixview(Matrixview *value);
    Q_INVOKABLE void removeStateAutomata(int index);
    Q_INVOKABLE void removeRuleAutomata(int index);
    Q_INVOKABLE void removeAllRulesAutomata();
    Q_INVOKABLE void removeAllStatesAutomata();
    Q_INVOKABLE QColor stateColorFromSquareIndex(int index);
    Q_INVOKABLE void displayMatrix();
    QString numbState() const;

signals:

    void probabilityChanged(QString probability);

    void posAndCountChanged(QString posAndCount);

    void stateToChangeToChanged(QString stateToChangeTo);

    void typeChanged(QString type);

    void dimensionChanged(QString dimension);

    void neighborhoodChanged(QString neighborhood);

    void maxGenerationsToSimulateChanged(QString maxGenerationsToSimulate);

    void sizeXChanged(QString sizeX);

    void sizeYChanged(QString sizeY);

    void stateNameChanged(QString name);

    void stateColorChanged(QString color);

    void numbStateChanged(QString numbState);

public slots:
void setProbability(QString probability);
void setPosAndCount(QString posAndCount);
void setStateToChangeTo(QString stateToChangeTo);
void setDimension(QString dimension);
void setType(QString type);
void setNeighborhood(QString neighborhood);
void setMaxGenerationsToSimulate(QString maxGenerationsToSimulate);
void setSizeX(QString sizeX);
void setSizeY(QString sizeY);
void setStateName(QString name);
void setStateColor(QString color);
void setNumbState(QString numbState);
};

#endif // INTERFACE_H
