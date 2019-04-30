#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rulestochasticdynamic.h"



float RuleStochasticDynamic::GetProbability(){ // on recalcul la probabilité de la règle

    float prob = 0.0;
    int posX = 0, posY = 0;
    for (int i = 0; i < automata.GetNeigborhoodPositions().size; i++) {
       posX = automata.GetNeigborhoodPositions()[i].first + currentCellX;
       posY = automata.GetNeigborhoodPositions()[i].second + currentCellY;
       prob += (automata.GetCellState(posX,posY)/* == Whatever the fuck that is*/);
    }
    
    prob /= 10;
    if(prob > 1) return 1.0;
    return prob;
}

