#pragma once
#include "automata.h"
#include "rule.h"
#include "ruledeterministic.h"
#include "rulestochastic.h"

class Parser
{
public:
    Parser();

    // Parse File télécharge l'information liée au fichier en argument
    // FileManager renvoie un char* qui est découpé en plusieurs tableaux de string qui ne comporteront pas les ";"
    // On obtient 4 tableaux de string, string* prelude, string* etats, string* regles, string* history
    // A chaque rencontre de ";" une nouvelle case de tableau est allouée
    // Le tableau du string se termine prochain délimiteur ("E;" ou "R;" ou "H;")
    // Une catégorie vide donne un string* nul, le délimiteur doit quand même être présent dans le fichier de sauvegarde
    // Les tableaux de string seront parsés séparément dans les petites fonctions de parsage
    // Aucune exception n'est gérée par ParseFile, elles seront gérées dans les fonctions spécifiques de parsing (sauf prélude)
    void  ParseFile(const  string* path);

    void SetAutomata(Automata* automata);

    string  GetDataToBeSaved(unsigned  int  startGen , unsigned  int  endGen);
    string  GetDataToBeSaved();
    void  ParseAndAddRules(string* index);//Fonction qui interprète les règles de l’automate.
    void  ParseAndAddStates(string* index);//Fonction qui interprète les états de l’automate.
    void  ParseAndAddType(string* index);//Fonction qui interprète la type de l’automate.
    void  ParseAndAddSize(string* index);//Fonction qui interprète la taille de l’automate
    void  ParseHistory(string* index);//Fonction parsant l’historique, chargée de récupérer les matrices de l’historiques’il existe,
                                      //elle peut lever l’exception (HISTORY) si par exemple il manque des générations.
                                      //Elle ajoute la génération à l’historique

    Automata *  GetAutomata();

    ~Parser();
private:
    Automata* automata;
    string  dataToParse;


    string  AutomataToString() ;//Fonctions qui calculent la représentation en chaîne de caractères de l’automate.
    string  HistoryToString();
    string  HistoryToString(uint startGen, uint endGen);
    string  RulesToString();

    //Parses an int, stopping right after ';'
    int ParseInt(string& index, uint& i);
};

