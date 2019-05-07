#pragma once

class Automata;
struct State;

#include <vector>

class Rule{
    protected:

    struct RuleParameters{
        int x,y;
        State* toCheckAgainst;
    };
        Automata* automata;
        State* toChangeInto;

        std::vector<RuleParameters> parameters;
        bool isComputePosition;
        int currentCellX, currentCellY;


    public:
        Rule(bool isComputePosition, State* toChangeInto, std::vector<RuleParameters> params);
        State& GetToChangeInto();
        std::vector<RuleParameters> GetParameters();
        bool GetIsComputePosition();
        virtual void Apply(int x, int y) = 0;
        virtual ~Rule() = 0;
};
