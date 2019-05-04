#pragma once
#include "automata.h"

class Parser
{
public:
    Parser();
    void  ParseFile(const  string* path);
    string  GetDataToBeSaved(unsigned  int  startGen , unsigned  int  endGen);
    string  GetDataToBeSaved();
    void  ParseAndAddRules(string* index);//Fonction qui interprète les regles de l’automate.
    void  ParseAndAddStates(string* index);//Fonction qui interprète les etats de l’automate.
    void  ParseAndAddType(string* index);//Fonction qui interprète la type de l’automate.
    void  ParseAndAddSize(string* index);//Fonction qui interprète la taille de l’automate
    Automata *  GetAutomata();
private:
    Automata* automata;
    string  dataToParse;

    void  ParseHistory(string* index);//Fonction parsant l’historique, chargée de récupérer les matrices de l’historiques’il existe,
                                      //elle peut lever l’exception (HISTORY) si par exemple il manque des générations.
                                      //Elle ajoute la génération à l’historique
    string  AutomataToString() ;//Fonctions qui calculent la représentation en chaîne de caractères de l’automate.
    string  HistoryToString();
    string  RulesToString();
};

