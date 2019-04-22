#include "automata.h"

Automata::Automata()
{

}

Automata::Automata(bool isNeighborhoodVonNeumann, bool isStocha, unsigned int sizeX, unsigned int sizeY,
                   vector<Rule> rules, vector<Automata::State> definedStates, vector<Generation> trace)
    : isVonNeighborhood(isNeighborhoodVonNeumann), isStocha(isStocha), sizeX(sizeX), sizeY(sizeY),
      rules(rules), definedStates(definedStates), generations(trace)
{
}
