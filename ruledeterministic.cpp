#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ruledeterministic.h"

void RuleDeterministic::Apply(int x, int y){

    /* pour computeposition :
    bool ruleTrue = true; // utilisé pour tester si tous les params sont vrais
    for( RuleParameters & Rparams : this->parameters) { // on parcours chaque paramètres de la règle
        if (GetCellState(x+Rparams.x,y+Rparams.y).name == Rparams.toCheckAgainst.name ){ // test entre la position relative entre la case central et celles de la règle pour voir si l'état est le même
            ruleTrue= ruleTrue && true;
        }
        else {
            ruleTrue=false;
        }
    }
    */

    if(this->isComputePosition){ // on verifie si on doit computeposition ou computecount
        // dans computePositon et l'autre compute le seul paramètre devrait être le vecteur de rulesParameters
        std::vector<std::pair<int, int>> positions;
        std::vector<State*> testState;
        for (unsigned long i = 1; i < this->parameters.size(); i++) {

            positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
            testState.push_back(this->parameters[i].toCheckAgainst);
        }
        if (ComputePosition(positions, testState,x,y){ // si la règle est effectivement vraie on applique
                automata.SetCell(x,y,this->toChangeInto); // changement de l'état de la cellule
                //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
        }
    }
    else {
        if (ComputeCount(this->parameters[1].x, this->parameters[1].toCheckAgainst,x,y){ // si la règle est effectivement vraie on applique
            automata.SetCell(x,y,this->toChangeInto); // changement de l'état de la cellule
            //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
            }
    }
}

