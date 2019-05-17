#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rule.h"

Rule::Rule(bool isComputePosition, State* toChangeInto, State* startingState, std::vector<RuleParameters> params){
    this->isComputePosition=isComputePosition;
    this->toChangeInto=toChangeInto;
    this->startingState=startingState;
    this->parameters=params;

    automata = nullptr;
}

State& Rule::GetToChangeInto(){

    return *this->toChangeInto;
}

State& Rule::GetStartingState(){

    return *this->startingState;
}

std::vector<Rule::RuleParameters> Rule::GetParameters(){

    return this->parameters;
}

bool Rule::GetIsComputePosition(){
    return this->isComputePosition;

}

Rule::~Rule(){};
