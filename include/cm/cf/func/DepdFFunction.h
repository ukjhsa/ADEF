#ifndef DEPD_F_FUNCTION_H
#define DEPD_F_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include "Function.h"
#include "Any.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

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
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        auto min_config = config.get_config("min");
        auto min = make_and_setup_type<BaseFunction>(min_config, pm);
        min->set_function_name("min");
        add_function(min);

        auto max_config = config.get_config("max");
        auto max = make_and_setup_type<BaseFunction>(max_config, pm);
        max->set_function_name("max");
        add_function(max);

        auto lower_bound_config = config.get_config("lower_bound");
        auto lower_bound = make_and_setup_type<BaseFunction>(lower_bound_config, pm);
        lower_bound->set_function_name("lower_bound");
        add_function(lower_bound);

        min_ = 0;
        max_ = 0;
        lower_bound_ = 0.0;
    }

    Object generate() override
    {
        // avoid min_ equal to zero
        if (std::abs(min_) < std::numeric_limits<Object>::epsilon()) {
            min_ = std::numeric_limits<Object>::epsilon();
        }

        if (std::abs(max_/min_) < 1) {
            return std::max(lower_bound_, 1 - std::abs(max_/min_));
        }
        else {
            return std::max(lower_bound_, 1 - std::abs(min_/max_));
        }
    }

    void update() override
    {
        auto min = get_function("min");
        min->update();
        min_ = min->generate();

        auto max = get_function("max");
        max->update();
        max_ = max->generate();

        auto lower_bound = get_function("lower_bound");
        lower_bound->update();
        lower_bound_ = lower_bound->generate();
    }

    unsigned int number_of_parameters() const override
    {
        return 0;
    }

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
