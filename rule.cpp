#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "rule.h"

Rule::Rule(bool isComputePosition, State* toChangeInto, std::vector<RuleParameters> params){
    this->isComputePosition=isComputePosition;
    this->toChangeInto=toChangeInto;
    this->parameters=params;

    automata = nullptr;
}

Rule::~Rule(){};
