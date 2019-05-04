#include "parser.h"

#include <iostream>
#include <string>
using namespace std;

Parser::Parser()
{

}

void Parser::SetAutomata(Automata *automata)
{
    this->automata = automata;
}

void  Parser::ParseFile(const string* path)
{

}

string  Parser::GetDataToBeSaved(unsigned  int  startGen , unsigned  int  endGen)
{
    return "";
}

string  Parser::GetDataToBeSaved()
{
    return "";
}

// UNFINISHED
void  Parser::ParseAndAddRules(string* index)
{/*
    string curRuleType;
    int sizeToParse = sizeof(index)/sizeof(*index);
    int nbrR = stoi(index[0]);

    if(index[1] != ";"){
        // lancer exception de format
    }

    for(int i = 2; i < sizeToParse; i++){

        // Vérification du bon formatage du string index
        if(index[i+1] != ";" || index[i+3] != ";" || index[i+5] != ";"){
            // lancer exception de format
        }

        // Création et instantiation de la règle courante
        curRuleType = index[i];
        if(curRuleType == "rulestochastic"){

        }
    }
    */
}

void  Parser::ParseAndAddStates(string* index)
{

}

void  Parser::ParseAndAddType(string* index)
{

}

// Ajouter la vérification du type de l'élément courant
void  Parser::ParseAndAddSize(string* index)
{
    // Vérification du nombre d'éléments
    int size = sizeof(index) / sizeof(index[0]);

    // Vérification du type des éléments
    // A IMPLEMENTER

    if(size < 3){
        // lancer une exception de format
    }

    int x = stoi(index[0]);
    int y = stoi(index[2]);

    // Vérification int > 0
    if(x < 0 || y < 0){
        // lancer une exception de format
    }

    // Instantiation de sizeX et sizeY
    automata->SetSizeX(static_cast<unsigned>(stoi(index[0])));
    automata->SetSizeY(static_cast<unsigned>(stoi(index[2])));
}

void  Parser::ParseHistory(string* index)
{

}

/*
 *  Prelude :
        SizeX ;SizeY ;
        isStocha ;
        Voisinage
    États :
        Nb_E ;
        Nom_Couleur;
        Nom_Etat <--- THIS HAS BEEN MODIFIED (ADDED) @Fab
    Règles :
        Nb_R ;
        Type ;EtatDep ;EtatArr ;lengthCond ;(x ;y ;EtatCond)* ;Proba ;EtatCond ;
    Historique :
        Nb_H ;
        genID ;
 * */
string  Parser::AutomataToString()
{
    if(automata != nullptr)
    {
        string strRepresentation = "";

        strRepresentation.append(to_string(automata->GetSizeX()));
        strRepresentation.append(";");

        strRepresentation.append(to_string(automata->GetSizeY()));
        strRepresentation.append(";");

        //1 == true, 0 == false
        strRepresentation.append(automata->GetIsStocha() ? "1" : "0");
        strRepresentation.append(";");

        //1 == true, 0 == false
        strRepresentation.append(automata->GetIsVonNeighborhood() ? "1" : "0");
        strRepresentation.append(";");

        strRepresentation.append(to_string(automata->GetStates().size()));
        strRepresentation.append(";");

        //HOW TO CONVERT FROM STR TO QCOLOR
        //  QColor q;
        // QString str(automata->GetStates()[0].color.name().toStdString().c_str());
        // q.setNamedColor(str);

        for (State s : automata->GetStates()) {
            strRepresentation.append(s.color.name().toStdString());
            strRepresentation.append(";");

            strRepresentation.append(s.name);
            strRepresentation.append(";");
        }

        return strRepresentation;
    }

   return "";
}

string  Parser::HistoryToString()
{
    string strRepresentation = "";

    return "";
}

//TODO : test (surtout me dire si cest la bonne facon de faire) (@alex)
//probleme sur le changement de gen, j'ai l'impression que ca reste bloqué sur la 1ère
string Parser::HistoryToString(uint startGen, uint endGen)
{
    string strRepresentation = "";
    uint i = startGen;
    automata->ChooseGen(i);

    if(automata->GetCurrentGen().generationID != NULL){
        strRepresentation.append(to_string(startGen));
        strRepresentation.append(";");

        strRepresentation.append(to_string(endGen));
        strRepresentation.append(";");

        for(automata->ChooseGen(i); i <= endGen; i++){
            strRepresentation.append(to_string(automata->GetCurrentGen().generationID));
            strRepresentation.append(";");
        }
        return strRepresentation;
    }
    return "";
}

string  Parser::RulesToString()
{

    string strRepresentation = "";

    strRepresentation.append(to_string(automata->GetRules().size()));
    strRepresentation.append(";");

    return "";
}
