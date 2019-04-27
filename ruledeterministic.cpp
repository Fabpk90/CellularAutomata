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
        if (ComputePosition(this->parameters){ // si la règle est effectivement vraie on applique
                SetCell(x,y,this->toChangeInto); // changement de l'état de la cellule
        }
    }
    else {
        if (ComputeCount(this->parameters){ // si la règle est effectivement vraie on applique
                SetCell(x,y,this->toChangeInto); // changement de l'état de la cellule
            }
    }
}

