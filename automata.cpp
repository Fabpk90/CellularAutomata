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
    currentGen = 0;
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
}


void Automata::SetType(bool b){
    isStocha = b;
}

void Automata::SetNeighborhood(bool b){
    isVonNeighborhood = b;

    neighborhood.clear();

    if(isVonNeighborhood)
    {
        FillNeighborhoodVonNeumann();
    }
    else {
        FillNeighborhoodMoore();
    }
}

void Automata::Simulate()
{

    Simulator::Simulate(*this);

}


void Automata::AddGeneration(Generation &generation)
{

    generations.push_back(generation);

    //SortGenerations();
}

void Automata::AddGenerations(vector<Generation> gens)
{

    generations = gens;
}

void Automata::AddState(State &state)
{
    definedStates.push_back(state);
}

void Automata::AddRule(Rule &rule)
{
    rules.push_back(&rule);
}

void Automata::SetMaxSimulations(uint maxSimulations)
{
    this->maxSimulations = maxSimulations;
}

uint Automata::GetMaxSimulations()
{
    return maxSimulations;
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
    //Invalide l'historique et supprime l'entrée du vecteur
    this->generations.clear();

    for (uint i = 0; i < definedStates.size(); ++i) {
        if(definedStates[i].color == toRemove.color)
            definedStates.erase(definedStates.begin() + i);
    }
}

void Automata::RemoveAllRules()
{
    for (uint i = 0; i < rules.size(); ++i) {
        delete rules[i];
    }

    rules.clear();
}

void Automata::RemoveAllStates()
{
    definedStates.clear();
}

void Automata::RemoveRule(const Rule &toRemove)
{
    vector<Rule*>::iterator it = rules.begin();
    while (it != rules.end())
    {
        if((*it) == &toRemove)
        {
            generations.clear();
            auto toDelete = *it;
            it = rules.erase(it);

            delete toDelete;
        }
        else {
            it++;
        }
    }

}

void Automata::SortGenerations()
{

    std::sort(generations.begin(), generations.end());
}


void Automata::SetCell(uint x, uint y, State &newState)
{

    bool found = false;

    for (uint i = 0; i < definedStates.size() && !found; ++i) {

        //ici on test juste la couleur
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
    generations[currentGen].cellMatrix[x * sizeY + y] = newState;
}


void Automata::SetAllCell(State &newState)
{
    //Cherche l'index de l'état

    bool found = false;
    uint stateIndex = 0;

    for (uint i = 0; i < definedStates.size() && !found; ++i) {


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

    if(definedStates.size() != 0)
    {
        for (uint i = 0; i < sizeX; ++i) {
            for (uint j = 0; j < sizeY; ++j) {
                generations[currentGen].cellMatrix[i*sizeY+j]
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


void Automata::NextGen()
{
    vector<Generation>::iterator it = generations.begin();
    bool found = false;

    cout << "Current GenID: " << generations[currentGen].generationID << endl;
    for(int i = 0; i < sizeX; i++)
    {
        for (int j = 0; j < sizeY; j++) {
            cout << GetCellState(i,j).name << " -- ";
        }
        cout << endl;
    }

    while(it != generations.end() && !found)
    {
        if(it == generations.end())
        {
            found = true;
        }
        else if(it->generationID == generations[currentGen].generationID)
        {
            found = true;

            if(currentGen + 1 != generations.size()){
                currentGen++;

                cout << endl <<  "Current GenID: " << generations[currentGen].generationID << endl;
                for(int i = 0; i < sizeX; i++)
                {
                    for (int j = 0; j < sizeY; j++) {
                        cout << GetCellState(i,j).name << " -- ";
                    }
                    cout << endl;
                }

            }
            else {
                cout << "gen not available(plus)" << endl;
            }

        }
        else
        {
            ++it;
        }
    }
    if(!found) cout << "gen not found" << endl;
}


void Automata::PreviousGen()
{
    vector<Generation>::iterator it = generations.begin();
    bool found = false;

    while(it != generations.end() && !found)
    {
        if(this->currentGen == 0)
        {
            found = true;
        }
        else if(it->generationID == generations[currentGen].generationID)
        {
            found = true;
            if(currentGen  != 0)
                currentGen--;
            else {
                cout << "gen not available (less)" << endl;
            }

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

State &Automata::GetCellState( int x,  int y)
{
    if(x < 0) x = sizeX - 1;
    else if(x >= sizeX) x = 0;

    if(y < 0) y = sizeY - 1;
    else if(y >= sizeY) y = 0;

    return definedStates[generations[currentGen].cellMatrix[x * sizeY + y]];
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


void Automata::FillNeighborhoodVonNeumann()
{
    neighborhood.push_back(std::make_pair(+1,0));
    neighborhood.push_back(std::make_pair(0,+1));
    neighborhood.push_back(std::make_pair(0,-1));
    neighborhood.push_back(std::make_pair(-1,0));

}

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
