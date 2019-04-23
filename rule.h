#ifndef RULE_H
#define RULE_H

#include <vector>

class Rule{

    struct RuleParameters{
        int x,y;
        State toCheckAgainst;
    };

    private:
        State toChangeInto;
        std::vector<RuleParameters> parameters;
        bool isComputePosition;
        virtual void Apply(int x, int y) = 0;

    public:
        Rule(bool isComputePosition, State toChangeInto, std::vector<RuleParameters> params, EconditionType condType);
        State GetToChangeInto();
        std::vector<RuleParameters> GetParameters();
        bool GetIsComputePosition();

        virtual ~Rule() = 0;
};
#endif // RULE_H
