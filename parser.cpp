#include "parser.h"

#include <iostream>
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

void  Parser::ParseAndAddRules(string* index)
{

}

void  Parser::ParseAndAddStates(string* index)
{

}

void  Parser::ParseAndAddType(string* index)
{

}
void  Parser::ParseAndAddSize(string* index)
{

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
    return "";
}

string  Parser::RulesToString()
{
    return "";
}
