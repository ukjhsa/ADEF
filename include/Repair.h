#ifndef REPAIR_H
#define REPAIR_H

#include <memory>
#include <cstddef>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Repository;
class Individual;
class Problem;

/**
@brief Repair is the abstract base class of repairing infeasible solution.

@par The configuration
Repair has no extra configurations.@n
See setup() for the details.
*/
class Repair : public Prototype, public EvolutionaryState
{
public:

    virtual ~Repair() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Repair> clone() const
    {
        return std::dynamic_pointer_cast<Repair>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from Repair, its configuration should be
- JSON configuration
@code
"Repair": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Repair infeasible solutions.
@param repos The Repository which contains infeasible solutions to repair.
*/
    virtual void repair(std::shared_ptr<Repository> repos) const;
/**
@brief Repair infeasible solution according to the problem.
@param individual The individual to be repaired.
@param problem The Problem which has the definition.
*/
    virtual void repair(std::shared_ptr<Individual> individual,
                        std::shared_ptr<const Problem> problem) const;
/**
@brief Repair infeasible solution by given function.
@param individual The individual to be repaired.
@param dimension The value of individual be repaired on specific dimension.
@param problem The Problem which has the definition.
*/
    virtual void repair_function(std::shared_ptr<Individual> individual,
                                 std::size_t dimension,
                                 std::shared_ptr<const Problem> problem) const = 0;

protected:

/**
@brief Find the nearest boundary of specific value in decision space.
@param gene The specific value.
@param problem The Problem which has the definition.
@param dimension The value of individual be repaired on specific dimension.
*/
    double find_nearest_bound(double gene,
                         std::shared_ptr<const Problem> problem,
                         std::size_t dimension) const;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // REPAIR_H
