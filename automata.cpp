#include "automata.h"

#include <iostream>

Automata::Automata() = default;

Automata::Automata(bool isNeighborhoodVonNeumann, bool isStocha, unsigned int sizeX, unsigned int sizeY,
                   vector<Rule> rules, vector<Automata::State> definedStates, vector<Generation> trace)
    : isVonNeighborhood(isNeighborhoodVonNeumann), isStocha(isStocha), sizeX(sizeX), sizeY(sizeY),
      rules(rules), definedStates(definedStates), generations(trace)
{
}

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
    // Classe regle non implémenté je laisse en commentaire pour l'instant
    /*vector<Rule>::iterator it = rules.begin();
    bool found = false;

    while(it != rules.end() && !found)
    {
        if(it->rulesID == toRemove)
        {
            found = true;

            it = rules.erase(it);

            cout << "removed rule " << &toRemove << endl;
            cout << "remaning rule " << generations.size() << endl;
        }
        else
        {
            ++it;
        }
    }*/
}

void Automata::SortGenerations()
{

}

void Automata::SetCell(int x, int y, Automata::State &newState)
{

}

void Automata::SetAllCell(Automata::State &newState)
{
    //TODO: verifier pour les comparaisons probleme de cast
    for (int i = 0; i < this->sizeX; i++) {
        for (int j = 0; j < this->sizeY; j++) {

            SetCell(i, j, newState);
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

}

void Automata::PreviousGen()
{

}

void Automata::ChooseGen(int i)
{

}

Automata::Generation &Automata::GetCurrentGen()
{
    return generations[currentGen];
}

Automata::State &Automata::GetCellState(unsigned int x, unsigned int y)
{
    //TODO: check si la formule est correcte
    return definedStates[generations[currentGen].cellMatrix[x * y + y]];
}

void Automata::FillNeighborhoodVonNeumann()
{

}

void Automata::FillNeighborhoodMoore()
{

}
