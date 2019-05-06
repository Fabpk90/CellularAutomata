#include "parser.h"
#include "filemanager.h"

#include <iostream>
#include <string>
using namespace std;

Parser::Parser()
{
    automata = nullptr;
    dataToParse = "";
}

void Parser::SetAutomata(Automata *automata)
{
    this->automata = automata;
}

void  Parser::ParseFile(const string* path)
{
    dataToParse = LoadData(path);
    ParseAndAddType(&dataToParse);
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
    if(automata != nullptr){

        strRepresentation.append(to_string(automata->GetGenerations().size()));
        strRepresentation.append(";");

        for (Generation g : automata->GetGenerations()){
            strRepresentation.append(to_string(g.generationID));
            strRepresentation.append(";");
        }

        return strRepresentation;
    }

    return "";
}

//Peut être gestion d'erreur à check et nombre de gen
string Parser::HistoryToString(uint startGen, uint endGen)
{
    string strRepresentation = "";

    if (automata != nullptr){
        for (Generation g : automata->GetGenerations()){
            if(g.generationID >= startGen && g.generationID <= endGen)
            {

                strRepresentation.append(to_string(g.generationID));
                strRepresentation.append(";");
            }
        }

        return strRepresentation;
    }

    return "";
}

//TODO : Test il manque Type ;EtatDep ;Proba ;EtatCond ;
// erreur : undefined references vers r.getparmaters et r.gettochangeinto
string  Parser::RulesToString()
{

    string strRepresentation = "";
    /*if(automata != nullptr){

        strRepresentation.append(to_string(automata->GetRules().size()));
        strRepresentation.append(";");
        for(Rule *r : automata->GetRules()){

            strRepresentation.append(r->GetToChangeInto().name); //Nom de l'etat d'arrivée
            strRepresentation.append(";");

            strRepresentation.append(to_string(r->GetParameters().size())); //longueur de la condition
            strRepresentation.append(";");


            for (unsigned long i = 1; i < r->GetParameters().size(); i++) {

                strRepresentation.append("(");
                strRepresentation.append(to_string(r->GetParameters()[i].x));
                strRepresentation.append(";");
                strRepresentation.append(to_string(r->GetParameters()[i].y));
                strRepresentation.append(";");
                strRepresentation.append(r->GetParameters()[i].toCheckAgainst->name);
                strRepresentation.append(";");
                strRepresentation.append(")");
                strRepresentation.append(";");
            }

                strRepresentation.append(); // Proba
                strRepresentation.append(";");
        }

        return strRepresentation;
    } */

    return "";
}
