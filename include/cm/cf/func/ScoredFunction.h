#ifndef SCORED_FUNCTION_H
#define SCORED_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include "Function.h"
#include "cm/ControlledObject.h"
#include "sf/ScoringFunction.h"

namespace adef {

/**
@brief ScoredFunction is the abstract base class of
all class that contains score and its scoring function.

ScoredFunction has the following feature:
- generate(): undefined.
- record(): undefined.
- update(): undefined.

@par The configuration
ScoredFunction has extra configurations:
- member
    - name: "scoring_function"
    - value: object configuration which is the class derived from
             ScoringFunction.
.
See setup() for the details.
*/
template<typename T>
class ScoredFunction : public Function<T>
{
public:

/// The type of score
    using Score = double;

    ScoredFunction() = default;
    ScoredFunction(const ScoredFunction& rhs) : Function<T>(rhs)
    {
        if (rhs.scoring_function_) {
            scoring_function_ = rhs.scoring_function_->clone();
        }
    }
    virtual ~ScoredFunction() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ScoredFunction> clone() const
    {
        return std::dynamic_pointer_cast<ScoredFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the @em Class which is derived from ScoredFunction
and has the following configuration:
- scoring_function: SuccessScoringFunction
.
its configuration should be
- JSON configuration
@code
"SomeThing" : {
    "classname" : "Class",
    "scoring_function" : {
        "classname" : "SuccessScoringFunction"
    }
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override
    {
        auto scoring_function_config = config.get_config("scoring_function");
        scoring_function_ = make_and_setup_type<ScoringFunction>(scoring_function_config, pm);
    }


protected:

/// The scoring function.
    std::shared_ptr<ScoringFunction> scoring_function_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // SCORED_FUNCTION_H
