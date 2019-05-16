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

// A COMPLETER
// Lance exception, à mettre dans un try catch
void  Parser::ParseFile(const string* path)
{
    //dataToParse = LoadData(path);
    dataToParse = "12;15;1;0;E;3;red;infected;black;dead;green;healthy;R;H;";
    string tailleT = "";
    string typeT = "";
    string statesT = "";
    string rulesT = "";
    string historyT = "";
    int cpt = 0; // compteur de points virgules pour différencier tailleT et typeT (qui à eux deux forment le prélude)

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
        while(i < dataToParse.length()){
            historyT += dataToParse[i];
            i++;
        }
    }

    cout << "Here's the wonderful mess P: " << tailleT << typeT << statesT << rulesT << historyT << endl;

    // Distribuer les tâches de parsing
    try {
        cout << cpt << endl;
        if(cpt == 4){
            ParseAndAddSize(&tailleT);
            ParseAndAddType(&typeT);
        }
        else throw string("Wrong prelude format");
    }
    catch(string const& error){
        cout << error << endl;
    }

    // Parsing Etats, Règles, Historique
    try {
        ParseAndAddStates(&statesT);
        ParseAndAddRules(&rulesT);
        ParseHistory(&historyT);

    } catch (string const& error) {
        cout << error << endl;
    }

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

void  Parser::ParseAndAddRules(string* index)
{

}

// Not tested nor approved
void  Parser::ParseAndAddStates(string* index)
{
    cout << *index << endl;
    cout << index->size() << endl;
    int sizeIndex = index->size();
    int cpt = 0;
    int cptVerifNbStates = 0;
    int i = 0;
    string nbStatesS = "";
    int nbStates = 0;
    int ascii = 0;

    if(sizeIndex < 3){
        throw(string("ParseAndAddStates : Minimum number of arguments not met"));
    }

    // Parsing jusqu'au NbStates
    while(cpt < 2 || (cpt == 2 && index[0][i] == ';')){
        if(index[0][i] == ';'){
            cpt++;
        }
        // premier ';' celui apres E donc cpt > 1
        if(cpt >= 1){
            ascii = index[0][i];
            if(ascii >= 48 && ascii <= 57) nbStatesS += index[0][i];
            else if(ascii != ';' && (ascii < 48 || ascii > 57)) {
                throw(string("ParseAndAddStates : Number of States is not an int"));
            }
        }
        i++;
    }
    //

    cout << "Nb states = " << nbStatesS << endl;
    nbStates = stoi(nbStatesS);
    cout << "Nb states = " << nbStates << endl;

    // Vérification du bon nombre de ';' en fonction du nombre d'états
    for(int k = i; k < sizeIndex; k ++){
        ascii = index[0][k];
        if(ascii == ';') cptVerifNbStates++;
    }
    if(cptVerifNbStates != 2 * nbStates) throw(string("ParseAndAddStates : Wrong Number of arguments"));
    // Jusque là tout est okay


    // Parsing des états

}

// Testé et approuvé par Amélie Le Roux lol
// Lance les exceptions de parsing
void  Parser::ParseAndAddType(string* index)
{
    if(index->size() != 4){
        throw(string("ParseAndAddType : Wrong number of arguments"));
    }

    int asciiType = index[0][0];
    int asciiNei = index[0][2];

    if(asciiType != 48 && asciiType != 49){
        throw(string("ParseAndAddType : Type isStocha is neither 0 or 1"));
    }
    if(asciiNei != 48 && asciiNei != 49){
        throw(string("ParseAndAddType : Type isVonNeumann is neither 0 or 1"));
    }

    automata->SetType(asciiType - 48);
    automata->SetNeighborhood(asciiNei - 48);
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
        if((ascii < 48 || ascii > 57) && (ascii != ';')){
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
