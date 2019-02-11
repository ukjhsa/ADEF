#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <memory>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Random;
class Problem;
class Population;
class Individual;

/**
@brief Initializer initializes initial values of the individual.

Call initialize() to initialize.

@par The configuration
Initializer has no extra configurations.@n
See setup() for the details.
*/
class Initializer : public Prototype, public EvolutionaryState
{
public:

    virtual ~Initializer() = default;
    Initializer& operator=(const Initializer& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Initializer> clone() const
    {
        return std::dynamic_pointer_cast<Initializer>(clone_impl());
    }
/**
@brief Set up the internal states.

Initializer's configuration should be
- JSON configuration
@code
"Initializer" : {
    "classname" : "Initializer"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

    virtual void init(std::shared_ptr<Repository> repos) override;

/**
@brief Evaluate an individual with specific problem.
*/
    virtual void initialize(std::shared_ptr<Repository> repos) const;
/**
@brief Evaluate a value by this initialization function.
*/
    virtual void initialization_function(
                                 std::shared_ptr<const Problem> problem,
                                 std::shared_ptr<Individual> individual) const;

protected:

    std::shared_ptr<Random> random_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Initializer>(*this);
    }
};

}

#endif

