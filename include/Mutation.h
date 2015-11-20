#ifndef MUTATION_H
#define MUTATION_H

#include <memory>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;

/**
@brief Mutation is the abstract base class of mutation.

Call mutate() to mutate.

@par The configuration
Mutation has no extra configurations.@n
See setup() for the details.
*/
class Mutation : public Prototype, public EvolutionaryState
{
public:

    virtual ~Mutation() = default;
    Mutation& operator=(const Mutation& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Mutation> clone() const
    {
        return std::dynamic_pointer_cast<Mutation>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from Mutation, its configuration should be
- JSON configuration
@code
"Mutation": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Mutate.
@param repos The Repository which contains information to mutate.
*/
    virtual void mutate(std::shared_ptr<Repository> repos) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif

