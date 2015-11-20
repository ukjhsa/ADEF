#ifndef MAX_FITNESS_CONTROL_UPDATE_H
#define MAX_FITNESS_CONTROL_UPDATE_H

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
@brief MaxFitnessControlUpdate updates internal states by
the maximum fitness value of the current population.

@par Requirement
record parameters into Function:
- name "max"
.

@par The configuration
MaxFitnessControlUpdate has no extra configurations.@n
See setup() for the details.
*/
class MaxFitnessControlUpdate : public ControlUpdate
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<MaxFitnessControlUpdate> clone() const
    {
        return std::dynamic_pointer_cast<MaxFitnessControlUpdate>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the MaxFitnessControlUpdate,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "MaxFitnessControlUpdate"
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
        double max_fitness = find_max_fitness(repos->population());
        auto succ = function->record({max_fitness}, "max");
        if (!succ) {
            throw std::runtime_error(
                 "No functions accept parameters \"max\" "
                 "in the \"" + function->function_name() + "\"");
        }
    }

private:

    double find_max_fitness(std::shared_ptr<const Population> pop) const
    {
        auto pop_size = pop->population_size();

        double max = pop->at(0)->fitness();
        for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
            double current = pop->at(idx)->fitness();
            if (max < current) {
                max = current;
            }
        }
        return max;
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<MaxFitnessControlUpdate>(*this);
    }
};

}

#endif // MAX_FITNESS_CONTROL_UPDATE_H
