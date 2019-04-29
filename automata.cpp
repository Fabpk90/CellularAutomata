#include "automata.h"

#include <iostream>
#include <algorithm>

Automata::Automata() = default;

Automata::Automata(bool isNeighborhoodVonNeumann, bool isStocha, unsigned int sizeX, unsigned int sizeY,
                   vector<Rule> rules, vector<Automata::State> definedStates, vector<Generation> trace)
    : isVonNeighborhood(isNeighborhoodVonNeumann), isStocha(isStocha), sizeX(sizeX), sizeY(sizeY),
      rules(rules), definedStates(definedStates), generations(trace)
{}

void Automata::Simulate()
{

}

void Automata::AddGeneration(Automata::Generation &generation)
{
    //TODO: ajouter la recherche de la génération
    generations.push_back(generation);

    cout << "Added a gen" << endl;
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
        }
        else
        {
            ++it;
        }
    }
}

void Automata::RemoveState(Automata::State &toRemove)
{

}

void Automata::RemoveRule(Rule &toRemove)
{
    // Classe regle non implémenté je laisse en commentaire pour l'instant (@Alex)
    //(@Fab) c'était du caca mon truc, il faut jeter tout l'historique aussi et remove la règle
}

void Automata::SortGenerations()
{
    //TODO: test !
    std::sort(generations.begin(), generations.end());
}

//TODO: test
void Automata::SetCell(uint x, uint y, Automata::State &newState)
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
    //TODO: check la formule, je suis pas sûr (@Fab)
    generations[currentGen].cellMatrix[x * y + y] = newState;
}

//TODO: test
void Automata::SetAllCell(Automata::State &newState)
{
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

}

const vector<Automata::State> &Automata::GetStates()
{
    return definedStates;
}

const vector<Rule> &Automata::GetRules()
{
    return rules;
}

const vector<pair<int, int> > &Automata::GetNeigborhoodPositions()
{
    return neighborhood;
}

void Automata::NextGen()
{
    //Generation generationID;
    //generationID = this->GetCurrentGen();

}

void Automata::PreviousGen()
{
    vector<Generation>::iterator it = generations.begin();
    bool found = false;
    this->currentGen = 1; // Je ne sais pas comment avoir la generation actuelle (@Alex)
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

            this->currentGen = it->generationID - 1;

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
    if(!found) cout << "gen not found" << endl;
}

Automata::Generation &Automata::GetCurrentGen()
{
    return generations[currentGen];
}

//TODO: test
Automata::State &Automata::GetCellState(unsigned int x, unsigned int y)
{
    //TODO: check si la formule est correcte (@Fab)
    return definedStates[generations[currentGen].cellMatrix[x * y + y]];
}

void Automata::FillNeighborhoodVonNeumann()
{

}

void Automata::FillNeighborhoodMoore()
{

}
