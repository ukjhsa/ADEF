#ifndef DE_VARIANT_X_H
#define DE_VARIANT_X_H

#include <memory>
#include <cstddef>
#include <vector>
#include "Prototype.h"

namespace adef {

class Individual;
class Population;

/**
@brief DEVariantX is the abstract base class of representing
the variant @e x in the DE algorithm.

@par The configuration
DEVariantX has no extra configurations.@n
See setup() for the details.
*/
class DEVariantX : public Prototype
{
public:

    virtual ~DEVariantX() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DEVariantX> clone() const
    {
        return std::dynamic_pointer_cast<DEVariantX>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from DEVariantX, its configuration should be
- JSON configuration
@code
"DEVariantX": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Return the number of needed indexes.
*/
    virtual unsigned int number_of_indexes() const = 0;

/**
@brief Return the base vector.
@param target_index The index of the target vector.
@param random_indexes The sequential indexes.
@param population The population to get individuals.
@return The base vector.
*/
    virtual std::shared_ptr<Individual> base_vector(
                        std::size_t target_index,
                        const std::vector<std::size_t>& random_indexes,
                        std::shared_ptr<const Population> population) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // DE_VARIANT_X_H
