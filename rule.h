#pragma once

#ifndef RULE_H
#define RULE_H

#include "automata.h"

#include <vector>

class Rule{
    protected:
    struct RuleParameters{
        int x,y;
        Automata::State* toCheckAgainst;
    };
        Automata& automata;
        Automata::State* toChangeInto;
        std::vector<RuleParameters> parameters;
        bool isComputePosition;
        int currentCellX, currentCellY;
        virtual void Apply(int x, int y) = 0;

    public:
        Rule(bool isComputePosition, Automata::State* toChangeInto, std::vector<RuleParameters> params);
        Automata::State& GetToChangeInto();
        std::vector<RuleParameters> GetParameters();
        bool GetIsComputePosition();

        virtual ~Rule() = 0;
};

#endif // RULE_H
