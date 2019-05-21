#ifndef RULESTOCHASTIC_H
#define RULESTOCHASTIC_H

#include "rule.h"

class RuleStochastic : public Rule
{
    private:

        float probability;

    public:

        RuleStochastic(bool isComputePosition, Automata* automata, State* toChangeInto, State* startingState,std::vector<RuleParameters> params, float probability);

        void Apply(int x, int y) override;
        int GetType() override; // retourne 0 si deterministe, 1 si stochastique et 2 si stochastique dynamique
        virtual float GetProbability() { // retourne la probabilité que la règle s'applique
            return this->probability;
        }

~RuleStochastic();

};


#endif // RULESTOCHASTIC_H
