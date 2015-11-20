#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <memory>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Problem;
class Population;
class Statistics;

/**
@brief Evaluator evaluates a value of the individual.

Call evaluate() to evaluate.

@par The configuration
Evaluator has no extra configurations.@n
See setup() for the details.
*/
class Evaluator : public Prototype, public EvolutionaryState
{
public:

    virtual ~Evaluator() = default;
    Evaluator& operator-(const Evaluator& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Evaluator> clone() const
    {
        return std::dynamic_pointer_cast<Evaluator>(clone_impl());
    }
/**
@brief Set up the internal states.

Evaluator's configuration should be
- JSON configuration
@code
"Evaluator" : {
    "classname" : "Evaluator"
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
    virtual void evaluate(std::shared_ptr<Population> pop,
                          std::shared_ptr<const Problem> problem,
                          std::shared_ptr<Statistics> statistics) const;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Evaluator>(*this);
    }
};

}

#endif
