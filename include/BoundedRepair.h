#ifndef BOUNDED_REPAIR_H
#define BOUNDED_REPAIR_H

#include <memory>
#include <cstddef>
#include "Repair.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Individual;
class Problem;

/**
@brief BoundedRepair repairs infeasible solution
by assigning the nearest boundary.

@par The configuration
ReflectiveRepair has no extra configurations.@n
See setup() for the details.
*/
class BoundedRepair : public Repair
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<BoundedRepair> clone() const
    {
        return std::dynamic_pointer_cast<BoundedRepair>(clone_impl());
    }
/**
@brief Set up the internal states.

BoundedRepair's configuration should be
- JSON configuration
@code
"Repair": {
    "classname" : "BoundedRepair"
}
@endcode
.
*/
    void setup(const Configuration& config,
               const PrototypeManager& pm) override;

    void init(std::shared_ptr<Repository> repos) override;

    void repair_function(std::shared_ptr<Individual> individual,
                         std::size_t dim,
                         std::shared_ptr<const Problem> problem) const override;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<BoundedRepair>(*this);
    }
};

}

#endif // BOUNDED_REPAIR_H
