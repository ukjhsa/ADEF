#ifndef ENVIRONMENTAL_SELECTION_H
#define ENVIRONMENTAL_SELECTION_H

#include <memory>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;

/**
@brief EnvironmentalSelection is the abstract base class of
selecting which individuals can survive.

Call select() to select which individuals can survive.

@par The configuration
EnvironmentalSelection has no extra configurations.@n
See setup() for the details.
*/
class EnvironmentalSelection : public Prototype, public EvolutionaryState
{
public:

    virtual ~EnvironmentalSelection() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<EnvironmentalSelection> clone() const
    {
        return std::dynamic_pointer_cast<EnvironmentalSelection>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from EnvironmentalSelection, its configuration should be
- JSON configuration
@code
"EnvironmentalSelection": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Select which individuals can survive.
@param repos The Repository which contains information to select.
*/
    virtual void select(std::shared_ptr<Repository> repos) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif
