#include "automata.h"

#include <iostream>

Automata::Automata()
{

}

Automata::Automata(bool isNeighborhoodVonNeumann, bool isStocha, unsigned int sizeX, unsigned int sizeY,
                   vector<Rule> rules, vector<Automata::State> definedStates, vector<Generation> trace)
    : isVonNeighborhood(isNeighborhoodVonNeumann), isStocha(isStocha), sizeX(sizeX), sizeY(sizeY),
      rules(rules), definedStates(definedStates), generations(trace)
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

            cout << "remaning gen " << generations.size() << endl;
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
