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
            std::vector<std::pair<int, int>> positions;
            std::vector<State> testState;
            for (unsigned long i = 0; i < this->parameters.size(); i++) {

                positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
                testState.push_back(this->parameters[i].toCheckAgainst);
            }
            if (ComputePosition(positions, testState,x,y){ // si la règle est effectivement vraie on applique
                    automata.SetCell(x,y,this->toChangeInto); // changement de l'état de la cellule
                    //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
            }
        }
        else {
            if (ComputeCount(this->parameters[0].x, this->parameters[0].toCheckAgainst,x,y){ // si la règle est effectivement vraie on applique
                automata.SetCell(x,y,this->toChangeInto); // changement de l'état de la cellule
                //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
            }

        }
    }
}

