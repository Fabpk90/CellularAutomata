#include "automata.h"
#include "simulator.h"

#include <iostream>
#include <algorithm>

Automata::Automata()
{
    currentGen = sizeX = sizeY = 0;
    isStocha = isVonNeighborhood = false;
    rules = vector<Rule*>();
    definedStates = vector<State>();
    generations = vector<Generation>();
    neighborhood = vector<pair<int,int>>();
    simulationThread = nullptr;
}

Automata::Automata(bool isNeighborhoodVonNeumann, bool isStocha, unsigned int sizeX, unsigned int sizeY,
                   vector<Rule*> rules, vector<State> definedStates, vector<Generation> trace)
    : isVonNeighborhood(isNeighborhoodVonNeumann), isStocha(isStocha), sizeX(sizeX), sizeY(sizeY),
      rules(rules), definedStates(definedStates), generations(trace)
{
    simulationThread = nullptr;
}

uint Automata::GetSizeX()
{
    return sizeX;
}

uint Automata::GetSizeY()
{
    return sizeY;
}

bool Automata::GetIsStocha()
{
    return isStocha;
}

bool Automata::GetIsVonNeighborhood()
{
    return isVonNeighborhood;
}

void Automata::SetSizeXY(uint x, uint y)
{
    sizeX = x;
    sizeY = y;

    generations = vector<Generation>();
    Generation g;
    g.generationID = 0;
    g.cellMatrix = vector<unsigned int> (sizeX*sizeY);

    generations.push_back(g);
}


void Automata::SetType(bool b){
    isStocha = b;
}

void Automata::SetNeighborhood(bool b){
    isVonNeighborhood = b;
}

void Automata::Simulate()
{
    if(simulationThread == nullptr)
    {
        simulationThread = new thread(&Simulator::Simulate, ref(*this));
    }
}

//Il manque le deplacement de la generation actuelle quand on ajoute une gen
void Automata::AddGeneration(Generation &generation)
{
    //TODO: ajouter la recherche de la génération
    //pour pas dupliquer une gén
    generations.push_back(generation);
    // currentGen = (uint)generations.size() - 1;
    cout << "Added a gen " <<generation.generationID<< endl;

    SortGenerations();
}

void Automata::AddGenerations(vector<Generation> gens)
{
    //TODO: bouger le currentGen ?
    generations = gens;
}

void Automata::AddState(State &state)
{
    cout << "Adding state " << state.name << endl;
    definedStates.push_back(state);
}

void Automata::AddRule(Rule &rule)
{
    cout << "Adding Rule" << endl;
    rules.push_back(&rule);
}

void Automata::RemoveGeneration(unsigned int index)
{
    vector<Generation>::iterator it = generations.begin();
    bool found = false;

    while(it != generations.end() && !found)
    {
        if(it->generationID == index)
        {
            found = true;

            it = generations.erase(it);

            cout << "removed gen " << index << endl;
            cout << "remaning gen " << generations.size() << endl;

            SortGenerations();
        }
        else
        {
            ++it;
        }
    }
}

void Automata::RemoveState(const State &toRemove)
{
    cout << "Removing state " << toRemove.name << endl;
    //Invalide l'historique et supprime l'entrée du vecteur (@Fab)
    this->generations.clear();

    for (uint i = 0; i < definedStates.size(); ++i) {
        if(definedStates[i].color == toRemove.color)
            definedStates.erase(definedStates.begin() + i);
    }

    cout << "Remaining states " << definedStates.size() << endl;
}

void Automata::RemoveRule(const Rule &toRemove)
{
    //TO TEST !
    vector<Rule*>::iterator it = rules.begin();
    bool found = false;

    while (it != rules.end())
    {
        if((*it) == &toRemove)
        {
            found = true;
            delete (*it);
        }
    }

    if(found)
    {
        generations.clear();
    }
}

void Automata::SortGenerations()
{
    //TODO: test !
    std::sort(generations.begin(), generations.end());
}

//TODO: test
void Automata::SetCell(uint x, uint y, State &newState)
{
    //Si ce truc là et copier coller plusieurs fois (@fab)
    //faire une fonction
    bool found = false;

    for (uint i = 0; i < definedStates.size() && !found; ++i) {

        //ici on test juste la couleur, le nom est trop lent (@Fab)
        if(definedStates[i].color == newState.color)
        {
            found = true;
            SetCell(x, y, i);
        }
    }
}

//TODO: test
void Automata::SetCell(uint x, uint y, uint newState)
{
    cout << "eheheh " << generations[currentGen].generationID << endl;
    cout << "tetppa " << generations[currentGen].cellMatrix.size() << endl;
    //TODO: check la formule, je suis pas sûr (@Fab)
    generations[currentGen].cellMatrix[x * y + y] = newState;
}

//TODO: test
void Automata::SetAllCell(State &newState)
{
    //Cherche l'index de l'état
    //Si ce truc là et copier coller plusieurs fois (@fab)
    //faire une fonction
    bool found = false;
    uint stateIndex = 0;

    for (uint i = 0; i < definedStates.size() && !found; ++i) {

        //ici on test juste la couleur, le nom est trop lent (@Fab)
        if(definedStates[i].color == newState.color)
        {
            stateIndex = i;
            found = true;
        }
    }


    for (uint i = 0; i < this->sizeX; i++) {
        for (uint j = 0; j < this->sizeY; j++) {
            SetCell(i, j, stateIndex);
        }
    }
}

void Automata::RandomizeCurrentGen()
{
    //srand(time(nullptr));
    if(definedStates.size() != 0)
    {
        for (uint i = 0; i < sizeX; ++i) {
            for (uint j = 0; j < sizeY; ++j) {
                generations[currentGen].cellMatrix[i*j+j]
                        = ((uint)rand()) % definedStates.size();
            }
        }
    }
    else {
        cout << "ERROR: unable to randomize the current gen, because 0 states are defined " << endl;
    }

}

const vector<Generation> &Automata::GetGenerations()
{
    return generations;
}

const vector<State> &Automata::GetStates()
{
    return definedStates;
}

const vector<Rule*> &Automata::GetRules()
{
    return rules;
}

const vector<pair<int, int> > &Automata::GetNeigborhoodPositions()
{
    return neighborhood;
}

//TODO : Test
void Automata::NextGen()
{
    vector<Generation>::iterator it = generations.begin();
    bool found = false;
    // Je ne sais pas comment avoir la generation actuelle (@Alex)
    while(it != generations.end() && !found)
    {
        if(it == generations.end())
        {
            found = true;
            cout << "No next gen" << endl;
        }
        else if(it->generationID == this->currentGen)
        {
            found = true;
            generations[currentGen++];

            cout << "choose gen " << this->currentGen << endl;
        }
        else
        {
            ++it;
        }
    }
    if(!found) cout << "gen not found" << endl;
}

//TODO : Test
void Automata::PreviousGen()
{
    vector<Generation>::iterator it = generations.begin();
    bool found = false;
    // Je ne sais pas comment avoir la generation actuelle (@Alex)
    while(it != generations.end() && !found)
    {
        if(this->currentGen == 0)
        {
            found = true;
            cout << "No previous gen" << endl;
        }
        else if(it->generationID == this->currentGen)
        {
            found = true;
            generations[currentGen--];

            cout << "choose gen " << this->currentGen << endl;
        }
        else
        {
            ++it;
        }
    }
    if(!found) cout << "gen not found" << endl;
}

void Automata::ChooseGen(unsigned int i)
{
    vector<Generation>::iterator it = generations.begin();
    bool found = false;

    while(it != generations.end() && !found)
    {
        if(it->generationID == i)
        {
            found = true;

            this->currentGen = i;

            cout << "choose gen " << i << endl;
        }
        else
        {
            ++it;
        }
    }
    if(!found) cout << "gen " << i << " not found" << endl;
}

Generation &Automata::GetCurrentGen()
{
    return generations[currentGen];
}

//TODO: test
State &Automata::GetCellState( int x,  int y)
{
    //TODO: check si la formule est correcte (@Fab)
    if(x < 0) x = sizeX - 1;
    else if(x > sizeX) x = 0;

    if(y < 0) y = sizeY - 1;
    else if(y > sizeY) y = 0;

    return definedStates[generations[currentGen].cellMatrix[x * y + y]];
}

Automata::~Automata()
{
    if(simulationThread != nullptr)
    {
        simulationThread->detach();
        delete simulationThread;
    }

    for (Rule* r : rules) {
        delete r;
    }
}

// TESTED
void Automata::FillNeighborhoodVonNeumann()
{
    neighborhood.push_back(std::make_pair(+1,0));
    neighborhood.push_back(std::make_pair(0,+1));
    neighborhood.push_back(std::make_pair(0,-1));
    neighborhood.push_back(std::make_pair(-1,0));
    /*
    cout << "printing vonneumnn" << endl;
    vector<pair<int,int>>::iterator it = neighborhood.begin();
    while(it != neighborhood.end()){
        cout << it->first << it->second << endl;
        ++it;
    }
    */
}

// TESTED
void Automata::FillNeighborhoodMoore()
{
    neighborhood.push_back(std::make_pair(+1,0));
    neighborhood.push_back(std::make_pair(0,+1));
    neighborhood.push_back(std::make_pair(0,-1));
    neighborhood.push_back(std::make_pair(-1,0));

    neighborhood.push_back(std::make_pair(+1,+1));
    neighborhood.push_back(std::make_pair(-1,+1));
    neighborhood.push_back(std::make_pair(-1,-1));
    neighborhood.push_back(std::make_pair(+1,-1));
}
