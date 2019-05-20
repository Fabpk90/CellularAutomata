#include "parser.h"
#include "filemanager.h"
#include "rule.h"
#include "rulestochasticdynamic.h"

#include <iostream>
#include <deque>
#include <string>
using namespace std;

Parser::Parser()
{
    automata = new Automata();
    dataToParse = "";
}

void Parser::SetAutomata(Automata *automata)
{
    delete this->automata;
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
    delete automata;
    automata = new Automata();

    try{
    dataToParse = LoadData(path);
    } catch(string const& error){
        cout<<error<<endl;
    }
    string tailleT = "";
    string typeT = "";
    string statesT = "";
    string rulesT = "";
    string historyT = "";
    int cpt = 0; // compteur de points virgules pour différencier tailleT et typeT (qui à eux deux forment le prélude)

    // Transformer le char* en string
    for(unsigned int i = 0; i < dataToParse.length(); i++){
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

        i += 2;//skips E;

        // états
        while(dataToParse[i] != 'R' && dataToParse.length() >= i){
            statesT += dataToParse[i];
            i++;
        }

        i += 2;//skips R;

        // règles
        while(dataToParse[i] != 'H' && dataToParse.length() >= i){
            rulesT += dataToParse[i];
            i++;
        }

        i += 2;//skips H;

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

Automata * Parser::GetAutomata(){
    return automata;
}

Parser::~Parser()
{
    delete automata;
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
    //TODO: test just before adding if the indexes are truly there (states[i] exists)
    //Position;1;0;8;(-1;1;0);(0;1;0);(1;1;0);(-1;0;0);(1;0;0);(-1;-1;0);(0;-1;0);(1;-1;0);99.9;
    uint i = 0;
    while(i != index->size())
    {
        string ruleType = "";

        while((*index)[i] != ';')
        {
            ruleType += (*index)[i++];
        }

        //cout << "Rule type: " << ruleType << endl;

        if(ruleType == "Position" || ruleType == "Count")
        {
            bool isComputePosition = ruleType == "Position" ? true : false;
            i++;//skipping the ;
            int indexStartState = 0;
            try {
                indexStartState = ParseInt(*index, i);
            } catch (string const& error) {
                throw (error);
            }

            //cout << "index start: " << indexStartState << endl;
            if(indexStartState >= 0) // if the index of the starting state is correct
            {
                int indexEndState = 0;
                try {
                    indexEndState = ParseInt(*index, i);
                } catch (string const& error) {
                    throw (error);
                }
                //cout << "index end: " << indexEndState << endl;
                if(indexEndState >= 0) // if the index of the changing state is correct
                {
                    int lengthStates = 0;
                    try {
                        lengthStates = ParseInt(*index, i);
                    } catch (string const& error) {
                        throw (error);
                    }
                     //cout << "length: " << lengthStates << endl;
                    if(lengthStates > 0) // TODO: more testing of the value !
                    {
                        vector<Rule::RuleParameters> parameters;
                        auto states = automata->GetStates();
                        Rule::RuleParameters param;
                        for (int j = 0; j < lengthStates; ++j) {
                             //cout << "Should be ( : " << (*index)[i] << endl;
                            i++; //skipping '('
                            try {
                            param.x = ParseInt(*index, i);
                            } catch (string const& error) {
                                throw (error);
                            }
                            try {
                            param.y = ParseInt(*index, i);
                            } catch (string const& error) {
                                throw (error);
                            }
                            int indexStates = 0;
                            try {
                                indexStates = ParseInt(*index, i);
                            } catch (string const& error) {
                                throw (error);
                            }
                            if(states.size() >= indexStates)
                            {
                                param.toCheckAgainst = &states[indexStates];
                            }
                            parameters.push_back(param);
                            //TODO: check for the state and add an error throw in parseint
                            //cout << "Should be ; : " << (*index)[i] << endl;
                            i++;//skipping ';'
                        }

                        if(index->at(i) != '\0' && index->at(i) != '\n') // if true, it is a stocha rule or stochadyn
                        {
                           //  cout << "Stocha or dyn" << endl;
                            string strProba = "";
                            while((*index)[i] != ';')
                            {
                                strProba += (*index)[i++];
                            }
                            i++;
                            float proba = atof(strProba.c_str());

                            //cout << "Proba: " << proba << endl;

                            if((*index)[i] != '\0') // it is definitely a stochadyn
                            {
                                int indexEtatCond = ParseInt(*index, i);
                                param.x = param.y = 0;
                                param.toCheckAgainst = &states[indexEtatCond];
                                vector<Rule::RuleParameters> vec;
                                vec.push_back(param);

                                for (int j = 0; j < parameters.size(); ++j) {
                                    vec.push_back(parameters[i]);
                                }

                                RuleStochasticDynamic* r = new RuleStochasticDynamic(isComputePosition, &states[indexEndState],&states[indexStartState], vec, proba);
                                automata->AddRule(*r);
                            }
                            else {
                                // cout << "stocha it is " << endl;
                                RuleStochastic* r = new RuleStochastic(isComputePosition, &states[indexEndState], &states[indexStartState], parameters, proba);
                                automata->AddRule(*r);
                            }
                        }
                        else {
                            // cout << "Deterministic " << endl;
                            RuleDeterministic* d = new RuleDeterministic(isComputePosition, &states[indexEndState], &states[indexStartState], parameters);
                            automata->AddRule(*d);
                        }
                    }
                }
                else {
                    throw(string("ParseAndAddRules : The endState is not correct"));
                }
            }
            else {
                throw(string("ParseAndAddRules : The startState is not correct"));
            }
        }
        else {
            throw(string("ParseAndAddRules : The type of the rule is not correct"));
        }
    }
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
    int parite = 0;
    State currentS;
    currentS.name = "";
    string currentcolorS = "";

    if(sizeIndex < 3){
        throw(string("ParseAndAddStates : Minimum number of arguments not met"));
    }

    // Parsing jusqu'au NbStates
    while(cpt < 1 || (cpt == 1 && index[0][i] == ';')){
        if(index[0][i] == ';'){
            cpt++;
        }
        // premier ';' celui apres E donc cpt > 1
        if(cpt >= 0){
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
    cout<<cptVerifNbStates<<endl;
    if(cptVerifNbStates != 2 * nbStates) throw(string("ParseAndAddStates : Wrong Number of arguments"));
    // Jusque là tout est okay

    // Parsing des états
    while(i < index->size()){
        ascii = index[0][i];
        while(ascii != ';'){
            ascii = index[0][i];
            if(parite % 2 == 0 && ascii != ';'){
                //QColor
                currentcolorS += index[0][i];
            }
            else if(ascii != ';'){
                //Name
                currentS.name += index[0][i];
            }
            i++;
            cout << (char) (ascii) << endl;
        }
        parite++;
        cout << parite << " " << i << " " << currentcolorS << endl;
        if(parite >= 1 && parite % 2){
            if(currentcolorS.size() != 7){
                throw(string("ParseAndAddStates : Color wrong format"));
            }
            else{
                int number = (int) strtol(&currentcolorS[1], NULL, 16);
                int r = number >> 16;
                int g = number >> 8 & 0xFF;
                int b = number & 0xFF;
                currentS.color.setRgb(r,g,b);
                if(currentS.color.isValid() == 0) throw(string("ParseAndAddStates : Color of state in wrong format"));
                currentcolorS = "";
            }
        }
        else{
            cout << currentS.name << currentS.color.rgb() << " " << currentS.color.isValid() << endl;
            automata->AddState(currentS);
            currentS.name = "";
        }
    }

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

//TODO : Test et ajout erreur
void  Parser::ParseHistory(string* index)
{
    cout << *index << endl;
    cout << index->size() << endl;
    int sizeIndex = index->size();
    int cpt = 0;
    int i = 0;
    string nbHistoryH = "";
    int nbHistory = 0;
    int ascii = 0;

    if(sizeIndex < 2){
        throw(string("ParseAndAddHistory : Minimum number of arguments not met"));
    }

    // Parsing jusqu'au NbHistory
    while(cpt < 1 || (cpt == 1 && index[0][i] == ';')){
        if(index[0][i] == ';'){
            cpt++;
        }
        // premier ';' celui apres H donc cpt > 1
        if(cpt >= 0){
            ascii = index[0][i];
            if(ascii >= 48 && ascii <= 57) nbHistoryH += index[0][i];
            else if(ascii != ';' && (ascii < 48 || ascii > 57)) {
                throw(string("ParseAndAddHistory : Number of History is not an int"));
            }
        }
        i++;
    }

    nbHistory = stoi(nbHistoryH);
    cout << "Nb History = " << nbHistory << endl;

    int asciiGenId = -1;
    string strRepresentation = "";
    vector<int> asciiStates;
    Generation g;

    for(int k = i; k < sizeIndex; k ++){

        ascii = index[0][k];
        if (ascii >= '0' && ascii <= '9'){

            asciiGenId = ascii - 48;
            g.generationID = asciiGenId;
            cout<< "GId : "<<g.generationID << endl;
        }else if(ascii == ';'){
            k++;
            ascii = index[0][k];
            if(ascii == '\0'){throw(string("ParseAndAddHistory : No state for the gen"));}
            while(ascii != ';'){

                if (ascii >= '0' && ascii <= '9' && ascii != ','){
                    strRepresentation.append(to_string(ascii-48));
                    k++;
                    ascii = index[0][k];
                }else if (ascii == ',' || ascii == ';') {

                    g.cellMatrix.push_back(stoi(strRepresentation));
                    cout<< "ajout"<<strRepresentation <<endl;
                    strRepresentation="";
                    k++;
                    ascii = index[0][k];
                }
            }
            g.cellMatrix.push_back(stoi(strRepresentation));
            cout<< "ajout "<<strRepresentation <<endl;
            strRepresentation = "";
            automata->AddGeneration(g);
        }else if(ascii != ';' && (ascii < 48 || ascii > 57)) {
            throw(string("ParseAndAddHistory : Number of History is not an int"));
        }
    }

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
        1 ;2 ;3 ;5 ;0 ;1 ;2 ;...=> Énumération des états des cellules des matrices constituant l’historique,le numéro correspond à la position de l’état dans le tableau des états.
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
            strRepresentation.append("(");
            for(unsigned long i = 0; i < g.cellMatrix.size(); i++){

                strRepresentation.append(to_string(g.cellMatrix.at(i)));
                strRepresentation.append(";");
            }

            strRepresentation.append(")");
        }

        return strRepresentation;
    }

    return "";
}

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

        if(generationsFound != 0){
            for (Generation g : automata->GetGenerations()){

                strRepresentation.append(to_string(g.generationID));
                strRepresentation.append(";");
                for(unsigned long i = 0; i < g.cellMatrix.size(); i++){

                    strRepresentation.append(to_string(g.cellMatrix.at(i)));
                    strRepresentation.append(",");
                }
                strRepresentation.pop_back();
                strRepresentation.append(";");
            }
            return strRepresentation;
        }
        return strRepresentation;
    }

    return "";
}

//TODO : Test il manque EtatDep ;EtatCond ;
string  Parser::RulesToString()
{

    string strRepresentation = "";
    if(automata != nullptr){

        strRepresentation.append(to_string(automata->GetRules().size())); //Nombre de règle
        strRepresentation.append(";");
        for(Rule *r : automata->GetRules()){

            strRepresentation.append(to_string(r->GetType())); //type : 0 = deterministe; 1 = stochastique; 2 =stochastique dynamique
            strRepresentation.append(";");
            strRepresentation.append(r->GetStartingState().name); //Nom de l'etat de depart
            strRepresentation.append(";");
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
            if(r->GetType() != 0){
                auto rStocha = dynamic_cast<RuleStochastic*>(r);
                strRepresentation.append(to_string(rStocha->GetProbability())); // Proba
                strRepresentation.append(";");
                if(r->GetType() == 2){

                    strRepresentation.append(to_string(r->GetParameters()[0].x)); // Etatcond
                    strRepresentation.append(";");
                    strRepresentation.append(to_string(r->GetParameters()[0].y));
                    strRepresentation.append(";");
                }
            }

            strRepresentation.append("\n");
        }

        return strRepresentation;
    }

    return "";
}

int Parser::ParseInt(string &index, uint &i)
{
    string str = "";
    while ((index)[i] != ';' && (index)[i] != ')')
    {
        str += (index)[i++];
    }
    i++; //skipping the next char

    if(str == "")
        throw(string("ParsingInt : Not a number"));

    return atoi(str.c_str());
}
