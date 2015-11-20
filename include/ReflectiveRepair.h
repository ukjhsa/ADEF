#ifndef REFLECTIVE_REPAIR_H
#define REFLECTIVE_REPAIR_H

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
@brief ReflectiveRepair repairs infeasible solution
by inversion through the nearest boundary.

If it still infeasible after doing a inversion through the nearest boundary,
then it is assigned the nearest boundary.

@par The configuration
ReflectiveRepair has no extra configurations.@n
See setup() for the details.
*/
class ReflectiveRepair : public Repair
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ReflectiveRepair> clone() const
    {
        return std::dynamic_pointer_cast<ReflectiveRepair>(clone_impl());
    }
/**
@brief Set up the internal states.

ReflectiveRepair's configuration should be
- JSON configuration
@code
"Repair": {
    "classname" : "ReflectiveRepair"
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
        return std::make_shared<ReflectiveRepair>(*this);
    }
};

}

#endif // REFLECTIVE_REPAIR_H
