#include "automata.h"
namespace Simulator {
    void Simulate(Automata& automata); // applique les règles à l'automate

    bool ComputePosition(std::vector<std::pair<int , int >> positions ,std::vector<State*> testState , int  targetX , int  targetY); // vérification en fonction des positions

    bool ComputeCount(int amount, State* &toCheckAgainst, int posX, int posY); // vérification en fonction du nombre
}



