#ifndef DE_VARIANT_Y_H
#define DE_VARIANT_Y_H

#include <memory>
#include <vector>
#include "Prototype.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Individual;
class Population;

/**
@brief DEVariantY returns the number of difference vector in
the variant @e y in the DE algorithm.

@par The configuration
DEVariantY has extra configurations:
- member
    - name: "number_of_difference_vector"
    - value: <tt>unsigned int</tt>
.
See setup() for the details.
*/
class DEVariantY : public Prototype
{
public:

    virtual ~DEVariantY() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DEVariantY> clone() const
    {
        return std::dynamic_pointer_cast<DEVariantY>(clone_impl());
    }
/**
@brief Set up the internal states.

If DEVariantY has the following configuration:
- number_of_difference_vector: 1
.
its configuration should be
- JSON configuration
@code
"DEVariantY" : {
    "classname" : "DEVariantY",
    "number_of_difference_vector" : 1
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

/**
@brief Return the number of needed indexes.
*/
    virtual unsigned int number_of_indexes() const;
/**
@brief Return the difference vector.
@param random_indexes The sequential indexes.
@param population The population to get individuals.
@return The difference vector.
*/
    std::vector<std::shared_ptr<Individual>> difference_vector(
                            const std::vector<std::size_t>& random_indexes,
                            std::shared_ptr<const Population> population) const;

private:

/**
@brief Return the difference vector from initial to terminal.
@param terminal The terminal.
@param initial The initial.
@return The difference vector.
*/
    std::shared_ptr<Individual> make_difference(
                            std::shared_ptr<const Individual> terminal,
                            std::shared_ptr<const Individual> initial) const;

private:

/**
@brief The number of difference vector.
*/
    unsigned int number_of_difference_vector_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<DEVariantY>(*this);
    }
};

}

#endif // DE_VARIANT_Y_H
