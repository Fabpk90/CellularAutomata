#ifndef RULE_H
#define RULE_H

#include <vector>

class Rule{


    protected:

        struct RuleParameters{
            int x,y;
            State toCheckAgainst;
        };

        Automata& automata;
        State toChangeInto;
        std::vector<RuleParameters> parameters;
        bool isComputePosition;
        int currentCellX, currentCellY;
        virtual void Apply(int x, int y) = 0;

    public:
        Rule(bool isComputePosition, State toChangeInto, std::vector<RuleParameters> params);
        State GetToChangeInto();
        std::vector<RuleParameters> GetParameters();
        bool GetIsComputePosition();

        virtual ~Rule() = 0;
};
#endif // RULE_H
