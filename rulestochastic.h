#ifndef RULESTOCHASTIC_H
#define RULESTOCHASTIC_H

#include "rule.h"

class RuleStochastic : public Rule
{
    private:

        float probability;

    public:

        RuleStochastic(bool isComputePosition, State* toChangeInto, State* startingState, std::vector<RuleParameters> params, float probability);
        //Le :Rule(les params) se fait que dans le .cpp on me dit

        void Apply(int x, int y) override; //Besoin de spécifier override ?
        int GetType() override;
        virtual float GetProbability(){
            return this->probability;
        }



};


#endif // RULESTOCHASTIC_H
