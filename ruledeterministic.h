#ifndef RULEDETERMINISTIC_H
#define RULEDETERMINISTIC_H

#include "rule.h"

class RuleDeterministic : public Rule
{
    public:

    RuleDeterministic(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params);

    void Apply(int x, int y) override; // application de la règle de façon détérministe

    int GetType() override; // retourne 0 si deterministe, 1 si stochastique et 2 si stochastique dynamique

    ~RuleDeterministic();

};

#endif // RULEDETERMINISTIC_H
