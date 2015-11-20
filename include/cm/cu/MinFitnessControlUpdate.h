#ifndef MIN_FITNESS_CONTROL_UPDATE_H
#define MIN_FITNESS_CONTROL_UPDATE_H

#include <memory>
#include <string>
#include <stdexcept>
#include "ControlUpdate.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Population.h"

namespace adef {

/**
@brief MinFitnessControlUpdate updates internal states by
the minimum fitness value of the current population.

@par Requirement
record parameters into Function:
- name "min"
.

@par The configuration
MinFitnessControlUpdate has no extra configurations.@n
See setup() for the details.
*/
class MinFitnessControlUpdate : public ControlUpdate
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<MinFitnessControlUpdate> clone() const
    {
        return std::dynamic_pointer_cast<MinFitnessControlUpdate>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is MinFitnessControlUpdate,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "MinFitnessControlUpdate"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
    }

    void update(std::shared_ptr<Repository> repos,
                std::shared_ptr<BaseControlParameter> parameter,
                std::shared_ptr<BaseFunction> function) const override
    {
        double min_fitness = find_min_fitness(repos->population());
        auto succ = function->record({min_fitness}, "min");
        if (!succ) {
            throw std::runtime_error(
                 "No functions accept parameters \"min\" "
                 "in the \"" + function->function_name() + "\"");
        }
    }

private:

    double find_min_fitness(std::shared_ptr<const Population> pop) const
    {
        auto pop_size = pop->population_size();

        double min = pop->at(0)->fitness();
        for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
            auto current = pop->at(idx)->fitness();
            if (min > current) {
                min = current;
            }
        }
        return min;
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<MinFitnessControlUpdate>(*this);
    }
};

}

#endif // MIN_FITNESS_CONTROL_UPDATE_H
