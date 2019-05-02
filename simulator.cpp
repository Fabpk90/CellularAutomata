#include "simulator.h"
Automata automata; // TEMPORAIRE POUR EVITER ERRRORS
bool ComputePosition(std::vector<std::pair<int , int >> positions ,std::vector<State*> testState , int  targetX , int  targetY){
    bool ruleTrue = true; // utilisé pour tester si tous les params sont vrais
    for(int i=0; i<positions.size(); i++)
    {
        if (automata.GetCellState(targetX+positions[i].first,targetY+positions[i].second).name == testState[i]->name ){ // test entre la position relative entre la case central et celles de la règle pour voir si l'état est le même
            ruleTrue= ruleTrue && true;
        }
        else {
            ruleTrue=false;
        }
    }
    return ruleTrue;
}

bool ComputeCount(int amount, State* &toCheckAgainst, int posX, int posY){

    return true;
};
