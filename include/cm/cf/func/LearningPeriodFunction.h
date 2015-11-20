#ifndef LEARNING_PERIOD_FUNCTION_H
#define LEARNING_PERIOD_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include "Function.h"
#include "Any.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief LearningPeriodFunction represents the behavior that
updates after a learning period.
@tparam T The type of the object.

LearningPeriodFunction has the following feature:
- generate(): return the object generated by the object component.
- record(): record parameters into the object component.
- update(): update the object component after a learning period.

@par Requirement
record parameters into Function:
- name "object"
- name "generation"
.

Now ADEF support many kinds of LearningPeriodFunction:
- ::IntegerLearningPeriodFunction.
- ::RealLearningPeriodFunction.
- ::IntegerControlLearningPeriodFunction.
- ::RealControlLearningPeriodFunction.

@par The configuration
LearningPeriodFunction has extra configurations:
- member
    - name: "object"
    - value: object configuration which is the class derived from
             Function.
- member
    - name: "learning_period"
    - value: <tt>unsigned int</tt>
.
It has default configurations:
- member
    - name: "generation"
    - value: ::IntegerVariableFunction
.
See setup() for the details.
*/
template<typename T>
class LearningPeriodFunction : public Function<T>
{
public:

/// @copydoc Function::Object
    using Object = typename Function<T>::Object;

/**
@brief The default constructor.

The default value of current period and learning period are 0.
*/
    LearningPeriodFunction() : learning_period_(0)
    {
    }
/**
@brief The copy constructor, but the current period renews.
*/
    LearningPeriodFunction(const LearningPeriodFunction& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<LearningPeriodFunction> clone() const
    {
        return std::dynamic_pointer_cast<LearningPeriodFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the ::RealLearningPeriodFunction and
has the following configuration:
- object: ::RealConstantFunction of value 0.5
- learning_period: 50
.
its configuration should be
- JSON configuration
@code
"SomeThing" : {
    "classname" : "RealLearningPeriodFunction",
    "object" : {
        "classname" : "RealConstantFunction",
        "value" : 0.5
    },
    "learning_period" : 50
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        auto object_config = config.get_config("object");
        auto object = make_and_setup_type<BaseFunction>(object_config, pm);
        object->set_function_name("object");
        Function<T>::add_function(object);

        auto generation = pm.make_type<BaseFunction>("IntegerVariableFunction");
        generation->set_function_name("generation");
        Function<T>::add_function(generation);

        learning_period_ = config.get_uint_value("learning_period");
    }

    Object generate() override
    {
        return Function<T>::get_function("object")->generate();
    }

    void update() override
    {
        auto generation = std::dynamic_pointer_cast<Function<int>>(
                                    BaseFunction::get_function("generation"));
        generation->update();
        auto generatio = generation->generate();

        if (generatio % learning_period_ == 0) {
            Function<T>::get_function("object")->update();
        }
    }

    unsigned int number_of_parameters() const override
    {
        return 1;
    }

private:

/// The learning period.
    unsigned int learning_period_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<LearningPeriodFunction>(*this);
    }
};

/**
@brief IntegerLearningPeriodFunction is the LearningPeriodFunction
that controls the integer number.
*/
using IntegerLearningPeriodFunction = LearningPeriodFunction<int>;
/**
@brief RealLearningPeriodFunction is the LearningPeriodFunction
that controls the real number.
*/
using RealLearningPeriodFunction = LearningPeriodFunction<double>;
/**
@brief IntegerControlLearningPeriodFunction is the LearningPeriodFunction
that controls the ::IntegerFunction.
*/
using IntegerControlLearningPeriodFunction = LearningPeriodFunction<std::shared_ptr<IntegerFunction>>;

/**
@brief RealControlLearningPeriodFunction is the LearningPeriodFunction
that controls the ::RealFunction.
*/
using RealControlLearningPeriodFunction = LearningPeriodFunction<std::shared_ptr<RealFunction>>;

}

#endif // LEARNING_PERIOD_FUNCTION_H
