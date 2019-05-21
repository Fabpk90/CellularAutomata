#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rulestochasticdynamic.h"
#include "automata.h"

RuleStochasticDynamic::RuleStochasticDynamic(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params,
                                             float probability):
    RuleStochastic(isComputePosition, automata, toChangeInto, startingState ,params, probability){};

float RuleStochasticDynamic::GetProbability(){ // on recalcul la probabilité de la règle


    float prob = 0.0;
    int posX = 0, posY = 0;

    for (int i = 0; i < automata->GetNeigborhoodPositions().size(); i++) {
       posX = automata->GetNeigborhoodPositions()[i].first + currentCellX;
       posY = automata->GetNeigborhoodPositions()[i].second + currentCellY;

       //On compte le nombre de fois qu'on à l'état dont dépend la probabilité dans le voisinage
       if(automata->GetCellState(posX,posY).color == this->parameters[0].toCheckAgainst->color)
            prob++;
    }
    
    //On forme la proba sur [0;1]
    prob /= 10;
    //La proba est au maximum de 1
    if(prob > 1) return 1.0;
    return prob;
}

RuleStochasticDynamic::~RuleStochasticDynamic()
{}

int RuleStochasticDynamic::GetType(){
    return 2;
}

