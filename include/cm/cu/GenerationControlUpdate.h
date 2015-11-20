#ifndef GENERATION_CONTROL_UPDATE_H
#define GENERATION_CONTROL_UPDATE_H

#include <memory>
#include <string>
#include <stdexcept>
#include "ControlUpdate.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Parameters.h"

namespace adef {

/**
@brief GenerationControlUpdate updates internal states by
the current number of generation.

@par Requirement
Take out parameters from Parameters:
- type <tt>unsigned int</tt> and name "generation"
.
record parameters into Function:
- name "generation"
.

@par The configuration
GenerationControlUpdate has no extra configurations.@n
See setup() for the details.
*/
class GenerationControlUpdate : public ControlUpdate
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<GenerationControlUpdate> clone() const
    {
        return std::dynamic_pointer_cast<GenerationControlUpdate>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the GenerationControlUpdate,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "GenerationControlUpdate"
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
        std::string name = "generation";
        auto generation = repos->parameters()->take_out<unsigned int>(name);
        auto succ = function->record({generation}, name);
        if (!succ) {
            throw std::runtime_error(
                 "No functions accept parameters \"" + name + "\" "
                 "in the \"" + function->function_name() + "\"");
        }
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<GenerationControlUpdate>(*this);
    }
};

}

#endif // GENERATION_CONTROL_UPDATE_H
