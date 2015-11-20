#ifndef MULTIPLE_CONTROL_FUNCTION_H
#define MULTIPLE_CONTROL_FUNCTION_H

#include <memory>
#include <cstddef>
#include <vector>
#include "ControlFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "func/BaseFunction.h"

namespace adef {

/**
@brief MultipleControlFunction manages multiple functions.

@par The configuration
MultipleControlFunction has extra configurations:
- member
    - name: "number_of_functions"
    - value: <tt>unsigned int</tt>
- member
    - name: "Function"
    - value: object configurations which represents Function.
.
See setup() for the details.
*/
class MultipleControlFunction : public ControlFunction
{
public:

    MultipleControlFunction() = default;
    MultipleControlFunction(const MultipleControlFunction& rhs) :
        ControlFunction(rhs)
    {
        functions_.reserve(rhs.functions_.size());
        for (auto&& func : rhs.functions_) {
            if (func) { functions_.push_back(func->clone()); }
            else { functions_.push_back(nullptr); }
        }
    }

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<MultipleControlFunction> clone() const
    {
        return std::dynamic_pointer_cast<MultipleControlFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If MultipleControlFunction has the following configuration:
- number_of_functions: 100
- Function: ::RealConstantFunction of object 0.5
.
its configuration should be
- JSON configuration
@code
"ControlFunction" : {
    "classname" : "MultipleControlFunction",
    "number_of_functions" : 100,
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
        auto size = config.get_uint_value("number_of_functions");
        functions_.reserve(size);

        auto function = make_and_setup_type<BaseFunction>("Function", config, pm);
        for(decltype(size) idx = 0; idx < size; ++idx) {
            functions_.push_back(function->clone());
        }
    }

    std::shared_ptr<BaseFunction> at(std::size_t index) override
    {
        return functions_.at(index);
    }

private:

/// The function.
    std::vector<std::shared_ptr<BaseFunction>> functions_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<MultipleControlFunction>(*this);
    }
};

}

#endif // MULTIPLE_CONTROL_FUNCTION_H
