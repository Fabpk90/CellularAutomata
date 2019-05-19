#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rulestochastic.h"
//#include "automata.h"
#include "simulator.h"

RuleStochastic::RuleStochastic(bool isComputePosition, State* toChangeInto, State* startingState,
                               std::vector<RuleParameters> params, float probability)
    : Rule(isComputePosition, toChangeInto,startingState , params)
{
    this->probability=probability;
}


void RuleStochastic::Apply(int x, int y){

    // pour l'aléatoire sur la proba :
    float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    if (randomNumber<=GetProbability()){ // si le resultat aléatoire est entre  0 et la proba on passe à la suite

        if(this->isComputePosition){ // on verifie si on doit computeposition ou computecount
            // dans computePositon et l'autre compute le seul paramètre devrait être le vecteur de rulesParameters
            std::vector<std::pair<int, int>> positions;
            std::vector<State*> testState;
            for (unsigned long i = 1; i < this->parameters.size(); i++) {

                positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
                testState.push_back(this->parameters[i].toCheckAgainst);
            }
            if (Simulator::ComputePosition(positions, testState,x,y)){ // si la règle est effectivement vraie on applique
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                    //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
            }
        }
        else {
            bool applyCount = true;
            for (unsigned long i = 1; this->parameters.size(); i++) {
                if(!Simulator::ComputeCount(this->parameters[i].x, this->parameters[i].toCheckAgainst,x,y))
                {
                    applyCount = false;
                    break;
                }
            }
            if (applyCount){  // si la règle est effectivement vraie on applique
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
            }
        }
    }
}

int RuleStochastic::GetType(){
    return 1;
}
