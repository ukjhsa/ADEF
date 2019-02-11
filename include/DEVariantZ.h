#ifndef DE_VARIANT_Z_H
#define DE_VARIANT_Z_H

#include <memory>
#include "Prototype.h"

namespace adef {

class Individual;
class Repository;

/**
@brief DEVariantZ is the abstract base class of representing
the variant @e z in the DE algorithm.

@par The configuration
DEVariantZ has no extra configurations.@n
See setup() for the details.
*/
class DEVariantZ : public Prototype
{
public:

    virtual ~DEVariantZ() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DEVariantZ> clone() const
    {
        return std::dynamic_pointer_cast<DEVariantZ>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from DEVariantZ, its configuration should be
- JSON configuration
@code
"DEVariantZ": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Initialize.
@param repos The Repository to get initialization informations.
*/
    virtual void init(std::shared_ptr<Repository> repos) = 0;
/**
@brief Produce a child from parents.
@param mutant_vector The mutated vector.
@param target_vector The target vector.
@param crossover_rate The crossover probability.
@return The trial vector.
*/
    virtual std::shared_ptr<Individual> crossover(
                                std::shared_ptr<const Individual> mutant_vector,
                                std::shared_ptr<const Individual> target_vector,
                                double crossover_rate) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // DE_VARIANT_Z_H
