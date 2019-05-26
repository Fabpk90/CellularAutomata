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
    cout << "(Proba is: " << probability << ") ";

    this->probability=probability;
    cout << "saving " << this->probability << endl;

}

float RuleStochastic::GetProbability()
{
    //cout << "(Proba is: " << probability << ") ";
    return this->probability;
}

void RuleStochastic::Apply(int x, int y){

    //Pour l'aléatoire sur la proba :
    float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


     // si le resultat aléatoire est entre  0 et la proba on passe à la suite
    cout << "GetProba is " << this->GetProbability() << endl;
    cout << "The Randy is " << randomNumber << endl;
    currentCellX = x;
    currentCellY = y;
    if(randomNumber<= this->GetProbability()){ // si le resultat aléatoire est entre  0 et la proba on passe à la suite

        if(this->isComputePosition){ // on verifie si on doit computeposition ou computecount

            //On prépare les vecteurs pour ComputePosition
            std::vector<std::pair<int, int>> positions;
            std::vector<State*> testState;
            for (unsigned long i = 1; i < this->parameters.size(); i++)
            {
                positions.push_back(std::make_pair(this->parameters[i].x,this->parameters[i].y));
                testState.push_back(this->parameters[i].toCheckAgainst);
            }

            cout << "Parameters length: " << this->parameters.size() << endl;
            cout << "Pos Vector length: " << positions.size() << endl;
            cout << "Parameters X: " << this->parameters[1].x << " / Y: " << this->parameters[1].y << endl;
            cout << "Pos Vector X: " << positions[0].first << " / Y: " << positions[0].second << endl;



            if (Simulator::ComputePosition(positions, testState,x,y)){ // si la règle est effectivement vraie on applique

                automata->NextGen();//On passe à la "nouvelle" génération pour pouvoir Set la cellule
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen(); //On retourne à la génération sur laquelle on fait les observations

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

            if (applyCount){  //si la règle est effectivement vraie on applique
                automata->NextGen();//On passe à la "nouvelle" génération pour pouvoir Set la cellule
                automata->SetCell(x,y, *toChangeInto); // changement de l'état de la cellule
                automata->PreviousGen();//On retourne à la génération sur laquelle on fait les observations

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
