#pragma once

class Automata;
struct State;

#include <vector>

class Rule{
    public:

        struct RuleParameters{
            int x,y;
            State* toCheckAgainst;
        };

        Rule(bool isComputePosition, State* toChangeInto, State* startingState,std::vector<RuleParameters> params);


        
        State& GetToChangeInto();
        void SetStateToChangeInto(State* toChangeInto);
        std::vector<RuleParameters> GetParameters();
        State& GetStartingState();
        bool GetIsComputePosition();
        virtual void Apply(int x, int y) = 0;
        virtual int GetType()=0; // retourne 0 si deterministe, 1 si stochastique et 2 si stochastique dynamique
        virtual ~Rule() = 0;
        
protected:
    Automata* automata;
    State* toChangeInto;
    State* startingState;

    std::vector<RuleParameters> parameters;
    bool isComputePosition;
    int currentCellX, currentCellY;
        
};
