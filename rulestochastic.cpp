#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rulestochastic.h"
//#include "automata.h"
#include "simulator.h"
#include <iostream>

RuleStochastic::RuleStochastic(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params,
                               float probability)
    : Rule(isComputePosition, automata, toChangeInto,startingState , params)
{
    this->probability=probability;
}


void RuleStochastic::Apply(int x, int y){

    // pour l'aléatoire sur la proba :
    float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    std::cout << "Ich bein stochastic: " << randomNumber << " GetProba: " << GetProbability() << endl;

    //if (randomNumber<=GetProbability()){ // si le resultat aléatoire est entre  0 et la proba on passe à la suite
    if(randomNumber <= 0.56)
    {
        if(this->isComputePosition){ // on verifie si on doit computeposition ou computecount
            // dans computePositon et l'autre compute le seul paramètre devrait être le vecteur de rulesParameters
            std::vector<std::pair<int, int>> positions;
            std::vector<State*> testState;
            for (unsigned long i = 1; i < this->parameters.size(); i++) {

                positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
                testState.push_back(this->parameters[i].toCheckAgainst);
            }
            std::cout << "Positions size: " << positions.size() << " Param size: " << this->parameters.size() << endl;
            std::cout << "States size: " << testState.size() << " State: " << this->parameters[1].toCheckAgainst->name << " In testState: " << testState[0]->name << endl;
            if (Simulator::ComputePosition(positions, testState,x,y)){ // si la règle est effectivement vraie on applique
                automata->NextGen();
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();
            }
        }
        else {
            bool applyCount = true;
            for (unsigned long i = 1; i < this->parameters.size(); i++) {
                if(!Simulator::ComputeCount(this->parameters[i].x, this->parameters[i].toCheckAgainst,x,y))
                {
                    applyCount = false;
                    break;
                }
            }
            if (applyCount){  // si la règle est effectivement vraie on applique
                automata->NextGen();
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();
            }
        }
    }
}

int RuleStochastic::GetType(){
    return 1;
}

RuleStochastic::~RuleStochastic()
{
    //delete toChangeInto;
    //delete startingState;

    /*for(RuleParameters r : parameters)
    {
        delete r.toCheckAgainst;
    }*/
}
