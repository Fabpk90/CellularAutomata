#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ruledeterministic.h"
//#include "automata.h"
#include "simulator.h"

RuleDeterministic::RuleDeterministic(bool isComputePosition, State* toChangeInto, std::vector<RuleParameters> params):
    Rule(isComputePosition, toChangeInto, params){};

void RuleDeterministic::Apply(int x, int y){


    if(this->isComputePosition){ // on verifie si on doit computeposition ou computecount
        // dans computePositon et l'autre compute le seul paramètre devrait être le vecteur de rulesParameters
        std::vector<std::pair<int, int>> positions;
        std::vector<State*> testState;
        for (unsigned long i = 1; i < this->parameters.size(); i++) {

            positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
            testState.push_back(this->parameters[i].toCheckAgainst);
        }
        if (ComputePosition(positions, testState, x, y)){ // si la règle est effectivement vraie on applique
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

