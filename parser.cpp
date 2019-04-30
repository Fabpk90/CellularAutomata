#include "parser.h"

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
        Nom_Couleur ;
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
