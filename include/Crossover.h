#ifndef CROSSOVER_H
#define CROSSOVER_H

#include <memory>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Repository;

/**
@brief Crossover is the abstract base class of crossover.

@par The configuration
Crossover has no extra configurations.@n
See setup() for the details.
*/
class Crossover : public Prototype, public EvolutionaryState
{
public:

    virtual ~Crossover() = default;
    Crossover& operator=(const Crossover& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Crossover> clone() const
    {
        return std::dynamic_pointer_cast<Crossover>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from Crossover, its configuration should be
- JSON configuration
@code
"Crossover": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Exchange information between parents and produce a child.
@param repos The Repository which contains information to do crossover.
*/
    virtual void crossover(std::shared_ptr<Repository> repos) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif
