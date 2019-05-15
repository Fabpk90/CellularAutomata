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

/*
 *
        SizeX; SizeY;
        isStocha;
        Voisinage;
    E;
        Nb_E;
        Nom_Couleur;
        Nom_Etat; <--- THIS HAS BEEN MODIFIED (ADDED) @Fab
    R;
        Nb_R;
        Type;EtatDep ;EtatArr;lengthCond;(x;y;EtatCond)*;Proba;EtatCond;
    H;
        Nb_H;
        genID;
 * */

// A TESTER
void  Parser::ParseFile(const string* path)
{
    //dataToParse = LoadData(path);
    dataToParse = "12;15;1;0;";
    string tailleT = "";
    string typeT = "";
    string statesT = "";
    string rulesT = "";
    string historyT = "";
    int cpt = 0; // compteur de points virgules pour différencier tailleT et typeT (qui a eux deux forment le prélude)

    // Transformer le char* en string
    for(int i = 0; i < dataToParse.length(); i++){
        // prélude
        while(dataToParse[i] != 'E' && dataToParse.length() >= i) {
            if(dataToParse[i] == ';'){
                cpt++;
            }
            if(cpt < 2 || (cpt == 2 && dataToParse[i] == ';')){
                tailleT += dataToParse[i];
            }
            else{
                typeT += dataToParse[i];
            }
            i++;
        }

        // états
        while(dataToParse[i] != 'R' && dataToParse.length() >= i){
            statesT += dataToParse[i];
            i++;
        }

        // règles
        while(dataToParse[i] != 'H' && dataToParse.length() >= i){
            rulesT += dataToParse[i];
            i++;
        }

        //historique
        if(dataToParse[i] != ';' && dataToParse.length() >= i){
            historyT += dataToParse[i];
        }
    }

    cout << "Here's the wonderful mess P: " << tailleT << typeT <<  "  S: " << statesT << " R: " << rulesT << " H: " << historyT << endl;

    // Distribuer les tâches de parsing
    // Parsing du prélude
    try {
        if(cpt == 4){
            ParseAndAddSize(&tailleT);
            ParseAndAddType(&typeT);
        }
        else throw string("Wrong prelude format");
    }
    catch(string const& error){
        cout << error << endl;
    }

    // Parsing des états
    ParseAndAddStates(&statesT);

    // Parsing des règles
    ParseAndAddRules(&rulesT);

    // Parsing historique
    ParseHistory(&historyT);
}

//TODO : test
string  Parser::GetDataToBeSaved(unsigned  int  startGen , unsigned  int  endGen)
{
    string data = "";

    data.append(AutomataToString());
    data.append(HistoryToString(startGen, endGen));
    data.append(RulesToString());
    if(data != "") return data;
    return "";
}

//TODO : test
string  Parser::GetDataToBeSaved()
{
    string data = "";

    data.append(AutomataToString());
    data.append(RulesToString());
    if(data != "") return data;
    return "";
}


// UNFINISHED
//index[Nb_R][Type][EtatDep][EtatArr][lengthCond]([x][y][etatcond])*[proba][etatcond]
// pas de ";" dans le tableau de string, seulement les arguments qui nous intéressent
void  Parser::ParseAndAddRules(string* index)
{

}

void  Parser::ParseAndAddStates(string* index)
{

}

void  Parser::ParseAndAddType(string* index)
{

}

// Testé et approuvé par Amélie Le Roux yé
// Lance exceptions de parsing
void  Parser::ParseAndAddSize(string* index)
{
    cout << "Parse and add size :" << *index << endl;

    string xs = ""; // x en string
    string ys = ""; // y en string
    int cpt = 0;
    int ascii = 0;

    // parsing d'index TESTED
    for(int i = 0; i < index->size(); i++){
        ascii = index[0][i];
        if(ascii < 48 || ascii > 57){
            throw(string("ParseAndAddSize : X or Y is not an int"));
        }
        if(ascii == ';'){
            cpt ++;
        }
        else if(cpt < 1){
            xs += ascii;
        }
        else{
            ys += ascii;
        }
    }

    int x = stoi(xs);
    int y = stoi(ys);

    // Vérification int > 0
    try {
        if(x < 0 || y < 0){
            throw(string("Wrong format ParseAndAddSize : SizeX or SizeY < 0"));
        }
    } catch (string const& error) {
        cerr << error << endl;
    }

    // Instantiation de sizeX et sizeY
    automata->SetSizeX(x);
    automata->SetSizeY(y);
}

void  Parser::ParseHistory(string* index)
{

}

/*
 *
        SizeX; SizeY;
        isStocha;
        Voisinage;
    E;
        Nb_E;
        Nom_Couleur;
        Nom_Etat; <--- THIS HAS BEEN MODIFIED (ADDED) @Fab
    R;
        Nb_R;
        Type;EtatDep(une cellule);EtatArr;lengthCond;(x;y;EtatCond)*;Proba(stoch);EtatCond(stochdyn);
    H;
        Nb_H;
        genID;
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
        strRepresentation.append("\n");

        for (Generation g : automata->GetGenerations()){

            strRepresentation.append(to_string(g.generationID));
            strRepresentation.append(";");
            strRepresentation.append("\n");
            for(unsigned long i = 0; i < g.cellMatrix.size(); i++){

                strRepresentation.append(to_string(g.cellMatrix.at(i)));
                strRepresentation.append(";");
            }

            strRepresentation.append("\n");
        }

        return strRepresentation;
    }

    return "";
}

//Peut être gestion d'erreur à check
string Parser::HistoryToString(uint startGen, uint endGen)
{
    string strRepresentation = "";
    uint generationsFound = 0;

    if (automata != nullptr){
        for (Generation g : automata->GetGenerations()){
            if(g.generationID >= startGen && g.generationID <= endGen)
            {
                generationsFound++;
            }
        }
        strRepresentation.append(to_string(generationsFound));
        strRepresentation.append(";");
        strRepresentation.append("\n");

        if(generationsFound != 0){
            for (Generation g : automata->GetGenerations()){

                strRepresentation.append(to_string(g.generationID));
                strRepresentation.append(";");
                strRepresentation.append("\n");
                for(unsigned long i = 0; i < g.cellMatrix.size(); i++){

                    strRepresentation.append(to_string(g.cellMatrix.at(i)));
                    strRepresentation.append(";");
                }
                strRepresentation.append("\n");
            }
            return strRepresentation;
        }
        return strRepresentation;
    }

    return "";
}

//TODO : Test il manque Type ;EtatDep ;Proba ;EtatCond ;
string  Parser::RulesToString()
{

    string strRepresentation = "";
    /*if(automata != nullptr){

        strRepresentation.append(to_string(automata->GetRules().type()));
        strRepresentation.append(";");
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

                //strRepresentation.append(); // Proba
                //strRepresentation.append(";");
        }

        return strRepresentation;
    }*/

    return "";
}
