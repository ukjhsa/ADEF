#ifndef DEPD_F_FUNCTION_H
#define DEPD_F_FUNCTION_H

#include <memory>
#include "Function.h"

namespace adef {

class Configuration;
class PrototypeManager;

/**
@brief DepdFFunction generates numbers according to
the procedure of the F value in the DEPD algorithm.

DepdFFunction has the following feature:
- generate(): return the number according to
the procedure of the F value in the DEPD algorithm.
- record(): record parameters into the min, max and/or lower bound component.
- update(): update values of min, max and lower bound.

@par Requirement
record parameters into Function:
- name "min"
- name "max"
- name "lower_bound"
.

ADEF supports many kinds of DepdFFunction:
- DepdFFunction.

@par The configuration
DepdFFunction has extra configurations:
- member
    - name: "min"
    - value: object configuration which is the class derived from
             Function.
- member
    - name: "max"
    - value: object configuration which is the class derived from
             Function.
- member
    - name: "lower_bound"
    - value: object configuration which is the class derived from
             Function.
.
See setup() for the details.
*/
class DepdFFunction : public Function<double>
{
public:

    using T = double;

/// @copydoc Function::Object
    using Object = typename Function<T>::Object;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DepdFFunction> clone() const
    {
        return std::dynamic_pointer_cast<DepdFFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the DepdFFunction and
has the following configuration:
- lower bound: ::RealConstantFunction of object 0.4
.
its configuration should be
- JSON configuration
@code
"SomeThing" : {
    "classname" : "DepdFFunction",
    "min" : {
        "classname" : "RealVariableFunction"
    },
    "max" : {
        "classname" : "RealVariableFunction"
    },
    "lower_bound" : {
        "classname" : "RealConstantFunction",
        "object" : 0.4
    }
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override;

    Object generate() override;

    void update() override;

    unsigned int number_of_parameters() const override;

private:

/// The value of the min of fitness.
    Object min_;
/// The value of the max of fitness.
    Object max_;
/// The value of the lower bound.
    Object lower_bound_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<DepdFFunction>(*this);
    }
};

}

#endif // DEPD_F_FUNCTION_H
