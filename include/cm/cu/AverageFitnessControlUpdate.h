#ifndef AVERAGE_FITNESS_CONTROL_UPDATE_H
#define AVERAGE_FITNESS_CONTROL_UPDATE_H

#include <memory>
#include <vector>
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
@brief AverageFitnessControlUpdate updates internal states by
the average fitness value of the current population.

@par Requirement
record parameters into Function:
- name "average"
.

@par The configuration
AverageFitnessControlUpdate has no extra configurations.@n
See setup() for the details.
*/
class AverageFitnessControlUpdate : public ControlUpdate
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<AverageFitnessControlUpdate> clone() const
    {
        return std::dynamic_pointer_cast<AverageFitnessControlUpdate>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the AverageFitnessControlUpdate,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "AverageFitnessControlUpdate"
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
        double average_fitness = find_average_fitness(repos->population());
        auto succ = function->record({average_fitness}, "average");
        if (!succ) {
            throw std::runtime_error(
                 "No functions accept parameters \"average\" "
                 "in the \"" + function->function_name() + "\"");
        }
    }

private:

    double find_average_fitness(std::shared_ptr<const Population> pop) const
    {
        auto pop_size = pop->population_size();

        double average = 0;
        for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
            average += pop->at(idx)->fitness();
        }
        if (pop_size != 0) {
                average /= pop_size;
        }
        return average;
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<AverageFitnessControlUpdate>(*this);
    }
};

}

#endif // AVERAGE_FITNESS_CONTROL_UPDATE_H
