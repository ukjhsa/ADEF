#ifndef DE_RAND_H
#define DE_RAND_H

#include <cstddef>
#include <memory>
#include <vector>
#include "DEVariantX.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Individual;
class Population;

/**
@brief DERand is the variant of taking random individual in
the variant @e x in the DE algorithm.

@par The configuration
DERand has no extra configurations.@n
See setup() for the details.
*/
class DERand : public DEVariantX
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DERand> clone() const
    {
        return std::dynamic_pointer_cast<DERand>(clone_impl());
    }
/**
@brief Set up the internal states.

DERand's configuration should be
- JSON configuration
@code
"DEVariantX" : {
    "classname" : "DERand"
}
@endcode
.
*/
    void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

    unsigned int number_of_indexes() const override;

    std::shared_ptr<Individual> base_vector(
                std::size_t target_index,
                const std::vector<std::size_t>& random_indexes,
                std::shared_ptr<const Population> population) const override;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<DERand>(*this);
    }
};

}

#endif // DE_RAND_H
