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

        //On prépare les vecteurs à envoyer à ComputePosition
        std::vector<std::pair<int, int>> positions;
        std::vector<State*> testState;
        for (unsigned long i = 0; i < this->parameters.size(); i++) {

            positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
            testState.push_back(this->parameters[i].toCheckAgainst);
        }

        if (Simulator::ComputePosition(positions, testState, x, y)){ // si la règle est effectivement vraie on applique

                automata->NextGen();  //On passe à la "nouvelle" génération pour pouvoir Set la cellule
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen(); //On retourne à la génération sur laquelle on fait les observations


        }
    }
    else {
        bool applyCount = true; //Il faut qu'applyCount reste vrai au travers de la boucle pour Set la nouvelle cellule
        for (unsigned long i = 1; i < this->parameters.size(); i++) {
            if(!Simulator::ComputeCount(this->parameters[i].x, this->parameters[i].toCheckAgainst,x,y))
            {
                applyCount = false;
                break;
            }
        }
        if (applyCount){ // si la règle est effectivement vraie on applique

                automata->NextGen(); //On passe à la "nouvelle" génération pour pouvoir Set la cellule
                automata->SetCell(x,y, *toChangeInto); //changement de l'état de la cellule
                automata->PreviousGen();//On retourne à la génération sur laquelle on fait les observations

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

