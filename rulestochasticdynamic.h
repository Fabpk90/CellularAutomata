#ifndef RULESTOCHASTICDYNAMIC_H
#define RULESTOCHASTICDYNAMIC_H

#include "rulestochastic.h"

class RuleStochasticDynamic : public RuleStochastic
{

    public:

        RuleStochasticDynamic(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params,
                              float probability);
        int GetType() override; // retourne 0 si deterministe, 1 si stochastique et 2 si stochastique dynamique
        float GetProbability() override; // retourne la probabilité après l'avoir recalculée

        ~RuleStochasticDynamic();
};


#endif // RULESTOCHASTICDYNAMIC_H
