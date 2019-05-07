#include "automata.h"

void Simulate(Automata& automata);

bool ComputePosition(std::vector<std::pair<int , int >> positions ,std::vector<State*> testState , int  targetX , int  targetY);

bool ComputeCount(int amount, State* &toCheckAgainst, int posX, int posY);

