#ifndef SINGLE_CONTROL_FUNCTION_H
#define SINGLE_CONTROL_FUNCTION_H

#include <memory>
#include <cstddef>
#include "ControlFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "func/BaseFunction.h"

namespace adef {

/**
@brief SingleControlFunction manages single function.

@par The configuration
SingleControlFunction has extra configurations:
- member
    - name: "Function"
    - value: object configurations which represents Function.
.
See setup() for the details.
*/
class SingleControlFunction : public ControlFunction
{
public:

    SingleControlFunction() = default;
    SingleControlFunction(const SingleControlFunction& rhs) :
        ControlFunction(rhs),
        function_(rhs.function_ ? rhs.function_->clone() : nullptr)
    {
    }

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<SingleControlFunction> clone() const
    {
        return std::dynamic_pointer_cast<SingleControlFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If SingleControlFunction has the following configuration:
- Function: ::RealConstantFunction of object 0.5
.
its configuration should be
- JSON configuration
@code
"ControlFunction" : {
    "classname" : "SingleControlFunction",
    "Function" : {
        "classname" : "RealConstantFunction",
        "object" : 0.5
    }
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        function_ = make_and_setup_type<BaseFunction>("Function", config, pm);
    }
/**
@copydoc ControlFunction::at()

It ignores @em index because there is only one function.
*/
    std::shared_ptr<BaseFunction> at(std::size_t index) override
    {
        return function_;
    }


private:

/// The function.
    std::shared_ptr<BaseFunction> function_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<SingleControlFunction>(*this);
    }
};

}

#endif // SINGLE_CONTROL_FUNCTION_H
