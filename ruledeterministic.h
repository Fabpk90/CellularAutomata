#ifndef RULEDETERMINISTIC_H
#define RULEDETERMINISTIC_H

#include "rule.h"

class RuleDeterministic : public Rule
{
    public:

    RuleDeterministic(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params);
    //Le :Rule(les params) se fait que dans le .cpp on me dit

    void Apply(int x, int y) override; //Besoin de spécifier override ?

    int GetType() override;

    ~RuleDeterministic();

};

#endif // RULEDETERMINISTIC_H
