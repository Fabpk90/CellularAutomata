#ifndef RULESTOCHASTICDYNAMIC_H
#define RULESTOCHASTICDYNAMIC_H

#include "rulestochastic.h"

class RuleStochasticDynamic : public RuleStochastic
{

    public:

        RuleStochasticDynamic(bool isComputePosition, State* toChangeInto, std::vector<RuleParameters> params, float probability);
        //Le :Rule(les params) se fait que dans le .cpp on me dit et pas oublier de mettre 0 par default pour la proba ! (moi du futur !)

    protected:

        float GetProbability() override;
};


#endif // RULESTOCHASTICDYNAMIC_H
