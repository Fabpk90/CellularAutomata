#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rulestochastic.h"


RuleStochastic::RuleStochastic(bool isComputePosition, State toChangeInto, std::vector<RuleParameters> params, EconditionType condType, float probability){
    this->isComputePosition=isComputePosition;
    this->toChangeInto=toChangeInto;
    this->parameters=params;
    this->probability=probability;
}


void RuleStochastic::Apply(int x, int y){

    // pour l'aléatoire sur la proba :
    clock_t t;
    int result = (clock() - t)%101; // on obtient un nombre entre 0 et 100 compris
    if (GetProbability()>=result){ // si le resultat aléatoire est entre  0 et la proba on passe à la suite

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
}

