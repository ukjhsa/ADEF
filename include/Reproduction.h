#ifndef REPRODUCTION_H
#define REPRODUCTION_H

#include <memory>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;

/**
@brief Reproduction is the abstract base class of reproducing offspring.

Call reproduce() to reproduce offspring.

@par The configuration
Reproduction has no extra configurations.@n
See setup() for the details.
*/
class Reproduction : public Prototype, public EvolutionaryState
{
public:

    virtual ~Reproduction() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Reproduction> clone() const
    {
        return std::dynamic_pointer_cast<Reproduction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from Reproduction, its configuration should be
- JSON configuration
@code
"Reproduction": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Reproduce offspring.
@param repos The Repository which contains information to reproduce offspring.
*/
    virtual void reproduce(std::shared_ptr<Repository> repos) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif
