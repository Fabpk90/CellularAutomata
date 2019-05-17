#ifndef RULESTOCHASTICDYNAMIC_H
#define RULESTOCHASTICDYNAMIC_H

#include "rulestochastic.h"

class RuleStochasticDynamic : public RuleStochastic
{

    public:

        RuleStochasticDynamic(bool isComputePosition, State* toChangeInto,State* startingState, std::vector<RuleParameters> params, float probability);
        //Le :Rule(les params) mettre 0 de base pour proba
        int GetType() override;
        float GetProbability() override;




};


#endif // RULESTOCHASTICDYNAMIC_H
