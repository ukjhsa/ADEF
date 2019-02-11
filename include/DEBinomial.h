#ifndef DE_BINOMIAL_H
#define DE_BINOMIAL_H

#include <memory>
#include "DEVariantZ.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Individual;
class Random;

/**
@brief DEBinomial is the variant of binomial crossover in
the variant @e z in the DE algorithm.

@par The configuration
DEBinomial has no extra configurations.@n
See setup() for the details.
*/
class DEBinomial : public DEVariantZ
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DEBinomial> clone() const
    {
        return std::dynamic_pointer_cast<DEBinomial>(clone_impl());
    }
/**
@brief Set up the internal states.

DEBinomial's configuration should be
- JSON configuration
@code
"DEVariantZ": {
    "classname" : "DEBinomial"
}
@endcode
.
*/
    void setup(const Configuration& config,
               const PrototypeManager& pm) override;

    void init(std::shared_ptr<Repository> repos) override;

    std::shared_ptr<Individual> crossover(
                                std::shared_ptr<const Individual> mutant_vector,
                                std::shared_ptr<const Individual> target_vector,
                                double crossover_rate) const override;

protected:

    std::shared_ptr<Random> random_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<DEBinomial>(*this);
    }
};

}

#endif
