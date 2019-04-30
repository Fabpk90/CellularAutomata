#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rulestochasticdynamic.h"



float RuleStochasticDynamic::GetProbability(){ // on recalcul la probabilité de la règle

    float prob = 0.0;
    int posX = 0, posY = 0;
    for (int i = 0; i < automata->GetNeigborhoodPositions().size; i++) {
       posX = automata->GetNeigborhoodPositions()[i].first + currentCellX;
       posY = automata->GetNeigborhoodPositions()[i].second + currentCellY;
       /*-----------------------------------------------
       CHECK FOR FUCKING LOOPS SOMEWHERE EITHER HERE OR
       IN GETCELLSTATE, JUST DON'T FORGET !
       -----------------------------------------------*/
       prob += (automata->GetCellState(posX,posY) == this->parameters[0].toCheckAgainst);
    }
    
    prob /= 10;
    if(prob > 1) return 1.0;
    return prob;
}

