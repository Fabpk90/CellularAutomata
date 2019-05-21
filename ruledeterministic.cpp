#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "ruledeterministic.h"
//#include "automata.h"
#include "simulator.h"
#include <iostream>

RuleDeterministic::RuleDeterministic(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params):
    Rule(isComputePosition, automata, toChangeInto, startingState, params){};

void RuleDeterministic::Apply(int x, int y){


    if(this->isComputePosition){ // on verifie si on doit computeposition ou computecount
        // dans computePositon et l'autre compute le seul paramètre devrait être le vecteur de rulesParameters
        std::vector<std::pair<int, int>> positions;
        std::vector<State*> testState;
        for (unsigned long i = 0; i < this->parameters.size(); i++) {

            positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
            testState.push_back(this->parameters[i].toCheckAgainst);
        }
        std::cout << "Positions size: " << positions.size() << " Param size: " << this->parameters.size() << endl;
        if (Simulator::ComputePosition(positions, testState, x, y)){ // si la règle est effectivement vraie on applique
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen

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
        if (applyCount){ // si la règle est effectivement vraie on applique
                automata->NextGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();//Cheat to protect the specs, remove if simulate is able to produce the NewGen
                //FAUT VOIR SI C'EST BIEN CA QU'Il FAUT FAIRE EN FONCTION DE LA PROCEDURALE
        }
    }
}

int RuleDeterministic::GetType(){
    return 0;
}

RuleDeterministic::~RuleDeterministic()
{
    delete toChangeInto;
    delete startingState;

    for(RuleParameters r : parameters)
    {
        delete r.toCheckAgainst;
    }
}

