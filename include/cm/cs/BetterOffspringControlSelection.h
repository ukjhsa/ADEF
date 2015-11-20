#ifndef BETTER_OFFSPRING_CONTROL_SELECTION_H
#define BETTER_OFFSPRING_CONTROL_SELECTION_H

#include <memory>
#include <cstddef>
#include <string>
#include <stdexcept>
#include "ControlSelection.h"
#include "cm/ControlledObject.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cp/ControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "cm/cf/func/Function.h"
#include "Population.h"

namespace adef {

/**
@brief BetterOffspringControlSelection updates internal states by
the condition of offspring is better than parent.

@par Requirement
Take out parameters from Parameters:
- type @c std::size_t and name "target_index"
.
record parameters into Function:
- name "object"
.

@par The configuration
BetterOffspringControlSelection has no extra configurations.@n
See setup() for the details.
*/
template<typename T>
class BetterOffspringControlSelection : public ControlSelection
{
public:

/// The type of the object
    using Object = typename ControlledObject<T>::Object;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<BetterOffspringControlSelection> clone() const
    {
        return std::dynamic_pointer_cast<BetterOffspringControlSelection>(clone_impl());
    }
/**
@brief Set up the internal states.

If ::RealBetterOffspringControlSelection is used.@
its configuration should be
- JSON configuration
@code
"ControlSelection": {
    "classname" : "RealBetterOffspringControlSelection"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
    }

    void select(std::shared_ptr<Repository> repos,
                std::shared_ptr<BaseControlParameter> parameter,
                std::shared_ptr<BaseFunction> function) const override
    {
        auto param = std::dynamic_pointer_cast<ControlParameter<Object>>(parameter);

        auto index = repos->parameters()->take_out<std::size_t>("target_index");
        auto parent = repos->population()->at(index);
        auto offspring = repos->offspring()->at(index);
        if (offspring->fitness() < parent->fitness()) {

            auto succ = function->record({param->load(index)},
                                         parent, offspring, "object");
            if (!succ) {
                throw std::runtime_error(
                         "No functions accept parameters \"object\" "
                         "in the \"" + function->function_name() + "\"");
            }
        }
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<BetterOffspringControlSelection>(*this);
    }
};

/**
IntegerBetterOffspringControlSelection is the BetterOffspringControlSelection that
controls the integer number.
*/
using IntegerBetterOffspringControlSelection = BetterOffspringControlSelection<int>;
/**
RealBetterOffspringControlSelection is the BetterOffspringControlSelection that
controls the real number.
*/
using RealBetterOffspringControlSelection = BetterOffspringControlSelection<double>;
/**
@brief IntegerControlBetterOffspringControlSelection is the BetterOffspringControlSelection that
controls the ::IntegerFunction.
*/
using IntegerControlBetterOffspringControlSelection = BetterOffspringControlSelection<std::shared_ptr<IntegerFunction>>;
/**
@brief RealControlBetterOffspringControlSelection is the BetterOffspringControlSelection that
controls the ::RealFunction.
*/
using RealControlBetterOffspringControlSelection = BetterOffspringControlSelection<std::shared_ptr<RealFunction>>;

}

#endif // BETTER_OFFSPRING_CONTROL_SELECTION_H
