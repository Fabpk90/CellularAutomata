#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "rule.h"

#include <vector>
#include <string>
#include <stdlib.h>

#include <QColor>

using namespace std;

class Automata {
public:
    struct Generation {
        unsigned int generationID; //identifie la génération, en lui donnant un nombre
        //contient la génération, peut être une matrice ou un vecteur.
        // La valeur des éléments de la mtrice sont des entiers non signés, ceux-ci corresponde à un indice du vecteur d'états
        //Avec cet indice, nous avons une correspondance entre la valeur de la matrice des cellules et le vecteur des règles
        //L'équation pour obtenir la position d'un cellule = row * columns + col
        vector<unsigned int> cellMatrix;
    };
    struct State{
        QColor color;
        string name;
    };
    Automata(); //constructeur vide, utile pour la création via l'interface
    //Constructeur pour créer un automate avec un historique, le booléen isNeighborhood va déterminer la fonction de remplissage du vecteur de voisinage.
    Automata(bool isNeighborhoodVonNeumann, bool isStocha, unsigned int sizeX,unsigned int sizeY, vector<Rule> rules, vector<State> definedStates,  vector<Generation> trace);

    void Simulate();// Fonction permettant de simuler notre automate. Simule MAX_ITERATION
    void AddGeneration(Generation& generation); // Ajoute une nouvelle génération au vecteur générations.Si la génération existe déjà, elle sera écrasée par celle passée en paramètre.
    void RemoveGeneration(unsigned int index);
    void RemoveState(State& toRemove);
    void RemoveRule(Rule& toRemove);
    void SortGenerations(); // Trie le vecteur de generations
    void SetCell(int x, int y, State& newState); // passe la cellule en x,y en newState
    void SetAllCell(State& newState); //passe toutes les cellules à l'état spécifié, de la génération actuelle
    void RandomizeCurrentGen(); // Rempli aléatoirement la génération actuelle
    const vector<State>& GetStates();
    const vector<Rule>& GetRules();
    const vector<pair<int, int>>& GetNeigborhoodPositions();

    //NextGen permet, comme son nom l'indique de passer à la génération suivante (dans le cas où celle-ci a déjà été simulée). Renvoie une exception si elle n'est pas disponible
    void NextGen();

    //PreviousGen permet de passer à la génération précédente (dans le cas où celle-ci existe). Renvoie une exception si elle n'est pas disponible
    void PreviousGen();

    // Permet de se déplacer dans les générations. Si la génération sélectionnée existe elle remplacera la génération actuelle, comme currentGen.
    // Le cas de règle stochastique ne permet pas explicitement de se déplacer dans les générations sans les re-calculées. Renvoie une exception si elle n'est pas disponible
    void ChooseGen(int i);

    Generation& GetCurrentGen();
    // retourne l'état à la position du vecteur des cellules. Prend en compte la nécessité de faire boucler la matrice sur elle-même tel un torus. row * columns + col
    State& GetCellState(unsigned int x,unsigned int y);
private:
    unsigned int sizeX, sizeY; //taille de la génération
    bool isStocha, isVonNeighborhood;
    unsigned int currentGen; //référence à la génération actuelle, présente dans le vecteur de générations
    vector<Rule> rules; //contient toutes les règles de l'automate
    vector<Generation> generations; //contient toutes les générations simulées
    vector<pair<int, int>> neighborhood; //vecteur qui contient le voisinage représenté par des paires de positions relatives
    vector<State> definedStates; //sert surtout pour l'interface, savoir les états définis

    //Les fonctions insèrent dans le vecteur de voisins les positions relatives pour le calcul du voisinage
    void FillNeighborhoodVonNeumann(); //Insère les 4 axes
    void FillNeighborhoodMoore(); // Insère les 8 axes
};

#endif // AUTOMATA_H
