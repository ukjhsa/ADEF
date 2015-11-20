#ifndef DE_ENVIRONMENTAL_SELECTION_H
#define DE_ENVIRONMENTAL_SELECTION_H

#include <memory>
#include "EnvironmentalSelection.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Population;
class Individual;

/**
@brief DEEnvironmentalSelection selects which individuals can survive
according to the DE algorithm.

select() calls ControlMechanism::select() of the parameter @em CR and @em F.

@par The configuration
DEEnvironmentalSelection has no extra configurations.@n
See setup() for the details.
*/
class DEEnvironmentalSelection : public EnvironmentalSelection
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DEEnvironmentalSelection> clone() const
    {
        return std::dynamic_pointer_cast<DEEnvironmentalSelection>(clone_impl());
    }
/**
@brief Set up the internal states.

DEEnvironmentalSelection's configuration should be
- JSON configuration
@code
"EnvironmentalSelection": {
    "classname" : "DEEnvironmentalSelection"
}
@endcode
.
*/
    void setup(const Configuration& config,
               const PrototypeManager& pm) override;

    void init(std::shared_ptr<Repository> repos) override;

    void select(std::shared_ptr<Repository> repos) const override;

private:

/**
@brief Select which individual can survive.
*/
    std::shared_ptr<Individual> select(
                                std::shared_ptr<const Individual> lhs,
                                std::shared_ptr<const Individual> rhs) const;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<DEEnvironmentalSelection>(*this);
    }
};

}

#endif
