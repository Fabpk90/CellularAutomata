#ifndef RULEDETERMINISTIC_H
#define RULEDETERMINISTIC_H

#include "rule.h"

class RuleDeterministic : public Rule
{
    public:

    RuleDeterministic(bool isComputePosition, State toChangeInto, std::vector<RuleParameters> params, EconditionType condType);
    //Le :Rule(les params) se fait que dans le .cpp on me dit

    void Apply(int x, int y) override; //Besoin de spécifier override ?
};

#endif // RULEDETERMINISTIC_H
