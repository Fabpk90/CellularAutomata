#include "parser.h"
#include "filemanager.h"
#include "rule.h"
#include "rulestochasticdynamic.h"

#include <iostream>
#include <deque>
#include <string>
#include <QString>
using namespace std;

Parser::Parser()
{
    automata = new Automata();
    dataToParse = "";
}

void Parser::SetAutomata(Automata *automata)
{
   // delete this->automata;
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


void  Parser::ParseFile(const string* path)
{
  /*  delete automata;
    automata = new Automata();
*/
    try{
    dataToParse = LoadData(path);
    } catch(string const& error){
        cout<<error<<endl;
    }

    cout << "Data loaded: " << dataToParse << endl;

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

string  Parser::GetDataToBeSaved(unsigned  int  startGen , unsigned  int  endGen)
{
    string data = "";
    string tmp = "";

    data.append(AutomataToString());

    tmp = RulesToString();

    if(tmp == "")
    {
        tmp = "R;0;";
    }

    data.append(tmp);
    tmp = HistoryToString(startGen, endGen);

    if(tmp == "")
    {
        tmp = "H;0;";
    }

    data.append(tmp);

    return data;
}

string  Parser::GetDataToBeSaved()
{
    string data = "";
    string tmp = "";


    data.append(AutomataToString());

    tmp = RulesToString();

    if(tmp == "")
    {
        tmp = "R;0;";
    }

    data.append(tmp);
    tmp = HistoryToString();

    if(tmp == "")
    {
        tmp = "H;0;";
    }

    data.append(tmp);

    return data;
}

void  Parser::ParseAndAddRules(string* index)
{
    if(index->at(0) != '0') // aucune règle à interpreter
    {
        uint i = 2;
        while(i+1 < index->size())
        {
            string ruleType = "";

            while((*index)[i] != ';')
            {
                ruleType += (*index)[i++];
            }

            if(ruleType == "Position" || ruleType == "Count")
            {
                bool isComputePosition = ruleType == "Position" ? true : false;
                i++;//skip ';'
                int indexStartState = 0;
                try {
                    indexStartState = ParseInt(*index, i);
                } catch (string const& error) {
                    throw (error);
                }
                if(indexStartState >= 0) // si l'indice de l'état de départ est correct, on peut continuer
                {
                    int indexEndState = 0;
                    try {
                        indexEndState = ParseInt(*index, i);
                    } catch (string const& error) {
                        throw (error);
                    }
                    if(indexEndState >= 0) // si l'indice de l'état d'arrivée est correct, on peut continuer
                    {
                        int lengthStates = 0;
                        try {
                            lengthStates = ParseInt(*index, i);
                        } catch (string const& error) {
                            throw (error);
                        }

                        if(lengthStates > 0)
                        {
                            vector<Rule::RuleParameters> parameters;
                            const vector<State>& states = automata->GetStates();
                            Rule::RuleParameters param;
                            for (int j = 0; j < lengthStates; ++j) { //chargement des paramamètres
                                param.toCheckAgainst = nullptr;
                                i++;
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
                                    State* check = new State();
                                    check->name = states[indexStates].name;
                                    check->color = states[indexStates].color;
                                    param.toCheckAgainst = check;
                                }
                                parameters.push_back(param);

                                i++;//skip ')'
                                i++;//skip ';'
                            }

                            State* stateStart = new State();
                            stateStart->name = states[indexStartState].name;
                            stateStart->color = states[indexStartState].color;

                            State* endState = new State();
                            endState->name = states[indexEndState].name;
                            endState->color = states[indexEndState].color;
                            //cout << "index at " << index->at(i) << endl;
                            if(index->size() != i && index->at(i) != '\n') //si vrai, c'est une stocha ou stochadyn
                            {
                                string strProba = "";
                                while((*index)[i] != ';')
                                {
                                    #ifdef __unix__
                                    if((*index)[i] == '.')
                                    {   strProba += ',';
                                        i++;
                                    }
                                    else
                                    #endif
                                    strProba += (*index)[i++];
                                }
                                i++;
                                float proba = atof(strProba.c_str());

                                /*cout << "StrProba: " << strProba << endl;
                                cout << "StrProba.c: " << strProba.c_str() << endl;
                                cout << "Proba: " << proba << endl;*/

                                if((*index)[i] != '\0' && index->at(i) != '\n') // c'est une règle stocha dyn
                                {
                                    int indexEtatCond = ParseInt(*index, i);
                                    param.x = param.y = 0;
                                    State* check = new State();
                                    check->name = states[indexEtatCond].name;
                                    check->color = states[indexEtatCond].color;
                                    param.toCheckAgainst = check;
                                    vector<Rule::RuleParameters> vec;
                                    vec.push_back(param);

                                    for (uint j = 0; j < parameters.size(); ++j) {
                                        vec.push_back(parameters[j]);
                                    }

                                    RuleStochasticDynamic* r = new RuleStochasticDynamic(isComputePosition, automata, endState, stateStart, vec, proba);
                                    automata->AddRule(*r);
                                }
                                else {
                                    param.x = param.y = 0;
                                    param.toCheckAgainst = nullptr;
                                    vector<Rule::RuleParameters> vec;
                                    vec.push_back(param);

                                    for (uint j = 0; j < parameters.size(); ++j) {
                                        vec.push_back(parameters[j]);
                                    }
                                    RuleStochastic* r = new RuleStochastic(isComputePosition, automata, endState, stateStart, vec, proba);
                                    automata->AddRule(*r);
                                }
                            }
                            else {
                                RuleDeterministic* d = new RuleDeterministic(isComputePosition,automata, endState, stateStart, parameters);

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

}

void  Parser::ParseAndAddStates(string* index)
{
    if(index->at(0) != '0'){
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
            ascii = index[0][i];
            if(ascii >= 48 && ascii <= 57) nbStatesS += index[0][i];
            else if(ascii != ';' && (ascii < 48 || ascii > 57)) {
                    throw(string("ParseAndAddStates : Number of States is not an int"));
                }
            i++;
        }

        nbStates = stoi(nbStatesS);

        // Vérification du bon nombre de ';' en fonction du nombre d'états
        for(int k = i; k < sizeIndex; k ++){
            ascii = index[0][k];
            if(ascii == ';') cptVerifNbStates++;
        }
        if(cptVerifNbStates != 2 * nbStates) throw(string("ParseAndAddStates : Wrong Number of arguments"));

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
            }
            parite++;
            if(parite >= 1 && parite % 2){
                if(currentcolorS.size() != 7){
                    throw(string("ParseAndAddStates : Color wrong format"));
                }
                else{
                    int number = (int) strtol(&currentcolorS[1], NULL, 16);
                    int r = number >> 16;
                    int g = number >> 8 & 0xFF;
                    int b = number & 0xFF;
                    currentS.color = QColor();
                    currentS.color.setRgb(r,g,b);
                    if(currentS.color.isValid() == 0) throw(string("ParseAndAddStates : Color of state in wrong format"));
                    currentcolorS = "";
                }
            }
            else{
                bool found = false;

                for (int i = 0; i < automata->GetStates().size(); ++i) {
                    if(currentS.name == automata->GetStates()[i].name)
                        found = true;
                }
                if(!found)
                    automata->AddState(currentS);

                currentS.name = "";
            }
        }
    }
}


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


void  Parser::ParseAndAddSize(string* index)
{
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
    automata->SetSizeXY(x, y);
}


void  Parser::ParseHistory(string* index)
{
    //cout << *index << endl;
    //cout << index->size() << endl;
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
    //cout << "Nb History = " << nbHistory << endl;
    if(nbHistory != 0 ){
        int asciiGenId = -1;
        string strRepresentation = "";
        vector<int> asciiStates;
        Generation g;
        bool isadded = false;

        for(int k = i; k < sizeIndex; k ++){
        isadded = false;
            ascii = index[0][k];
            if (ascii >= '0' && ascii <= '9'){

                asciiGenId = ascii - 48; //Lecture du genId
                g.generationID = asciiGenId;
                //cout<< "GId : "<<g.generationID << endl;
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

                        g.cellMatrix.push_back(stoi(strRepresentation)); // Ajout dans le vecteur d'etat

                        strRepresentation="";
                        k++;
                        ascii = index[0][k];
                    }
                }
                g.cellMatrix.push_back(stoi(strRepresentation)); // Ajout dans le vecteur d'etat

                strRepresentation = "";
                automata->AddGeneration(g);
                isadded = true;
                if(isadded && nbHistory-1 == g.generationID) k = 999999;// On sort de la boucle car il n'y a plus de gen

            }else if(ascii != ';' && (ascii < 48 || ascii > 57)) {
                throw(string("ParseAndAddHistory : Number of genid is not an int"));
            }
        }
    }
}

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

        strRepresentation.append("E;");
        strRepresentation.append(to_string(automata->GetStates().size()));
        strRepresentation.append(";");

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

        strRepresentation.append("H;");

        for (Generation g : automata->GetGenerations()){
            if(g.generationID >= startGen && g.generationID <= endGen)
            {
                generationsFound++;
            }
        }

        strRepresentation.append(to_string(generationsFound));
        strRepresentation.append(";");

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


string  Parser::RulesToString()
{

    string strRepresentation = "";
    if(automata != nullptr){

        strRepresentation.append("R;");

        strRepresentation.append(to_string(automata->GetRules().size())); //Nombre de règle
        strRepresentation.append(";");

        for(Rule *r : automata->GetRules()){
            //type : 0 = Position; 1 = Count
            if(r->GetType() == 0){
                strRepresentation.append("Position");
            }
            else{
                strRepresentation.append("Count");
            }
            strRepresentation.append(";");
            uint index = 0;
            for (uint i = 0; i < automata->GetStates().size(); ++i) {
                if(automata->GetStates()[i].color == r->GetStartingState().color
                       && automata->GetStates()[i].name == r->GetStartingState().name)
                {
                    index = i;
                }
            }
            strRepresentation.append(to_string(index)); //Nom de l'etat de depart
            strRepresentation.append(";");

            for (uint i = 0; i < automata->GetStates().size(); ++i) {
                if(automata->GetStates()[i].color == r->GetToChangeInto().color
                       && automata->GetStates()[i].name == r->GetToChangeInto().name)
                {
                    index = i;
                }
            }

            strRepresentation.append(to_string(index)); //Nom de l'etat d'arrivée
            strRepresentation.append(";");

            strRepresentation.append(to_string(r->GetParameters().size())); //longueur de la condition
            strRepresentation.append(";");


            for (unsigned long i = 0; i < r->GetParameters().size(); i++) {

                strRepresentation.append("(");
                strRepresentation.append(to_string(r->GetParameters()[i].x));
                strRepresentation.append(";");
                strRepresentation.append(to_string(r->GetParameters()[i].y));
                strRepresentation.append(";");
                for (uint j = 0; j < automata->GetStates().size(); ++j) {
                    if(r->GetParameters()[i].toCheckAgainst != nullptr
                            && automata->GetStates()[j].name == r->GetParameters()[i].toCheckAgainst->name)
                    {
                        index = j;
                    }
                }
                strRepresentation.append(to_string(index));
                strRepresentation.append(";");
                strRepresentation.append(")");
                strRepresentation.append(";");
            }
            if(r->GetType() != 0){
                auto rStocha = dynamic_cast<RuleStochastic*>(r);
                strRepresentation.append(to_string(rStocha->GetProbability())); // Proba
                strRepresentation.append(";");
                if(r->GetType() == 2){
                    int index = -1;
                    for (uint i = 0; i < automata->GetStates().size(); ++i) {
                        if(automata->GetStates()[i].name == r->GetParameters()[0].toCheckAgainst->name)
                            index = i;
                    }

                    strRepresentation.append(to_string(index)); // Etatcond
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
    cout << "<";
    while ((index)[i] != ';' && (index)[i] != ')')
    {
        cout << (index)[i];
        str += (index)[i++];
    }
    cout << ">" <<endl;
    i++; //saute le prochain char, qui est un délimiteur

    if(str == "")
        throw(string("ParsingInt : Not a number"));

    return atoi(str.c_str());
}
