#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rule.h"

Rule::Rule(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params){
    this->isComputePosition=isComputePosition;
    this->toChangeInto=toChangeInto;
    this->startingState=startingState;
    this->parameters=params;

    this->automata = automata;
}

State& Rule::GetToChangeInto(){

    return *this->toChangeInto;
}

State& Rule::GetStartingState(){

    return *this->startingState;
}
void Rule::SetStateToChangeInto(State *toChangeInto)
{
    this->toChangeInto = toChangeInto;
}

std::vector<Rule::RuleParameters> Rule::GetParameters(){

    return this->parameters;
}

bool Rule::GetIsComputePosition(){
    return this->isComputePosition;

}

Rule::~Rule(){};
