#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rulestochastic.h"
//#include "automata.h"
#include "simulator.h"

RuleStochastic::RuleStochastic(bool isComputePosition, State* toChangeInto,
                               std::vector<RuleParameters> params, float probability)
    : Rule(isComputePosition, toChangeInto, params)
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
            if (ComputePosition(positions, testState,x,y)){ // si la règle est effectivement vraie on applique
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                    //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
            }
            else {
                State currentState;
                currentState = automata->GetCellState(x,y);
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, currentState); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
            }
        }
        else {
            if (ComputeCount(this->parameters[1].x, this->parameters[1].toCheckAgainst,x,y)){ // si la règle est effectivement vraie on applique
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
            }
            else {
                State currentState;
                currentState = automata->GetCellState(x,y);
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, currentState); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
            }

        }
    }
}

