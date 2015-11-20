#ifndef CURRENT_FITNESS_CONTROL_UPDATE_H
#define CURRENT_FITNESS_CONTROL_UPDATE_H

#include <memory>
#include <cstddef>
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
@brief CurrentFitnessControlUpdate updates internal states by
the fitness value of current individual..

@par Requirement
Take out parameters from Parameters:
- type @c std::size_t and name "target_index"
.
record parameters into Function:
- name "current"
.

@par The configuration
CurrentFitnessControlUpdate has no extra configurations.@n
See setup() for the details.
*/
class CurrentFitnessControlUpdate : public ControlUpdate
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<CurrentFitnessControlUpdate> clone() const
    {
        return std::dynamic_pointer_cast<CurrentFitnessControlUpdate>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the CurrentFitnessControlUpdate,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "CurrentFitnessControlUpdate"
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
        auto index = repos->parameters()->take_out<std::size_t>("target_index");
        auto current_fitness = repos->population()->at(index)->fitness();
        auto succ = function->record({current_fitness}, "current");
        if (!succ) {
            throw std::runtime_error(
                 "No functions accept parameters \"current\" "
                 "in the \"" + function->function_name() + "\"");
        }
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<CurrentFitnessControlUpdate>(*this);
    }
};

}

#endif // CURRENT_FITNESS_CONTROL_UPDATE_H
