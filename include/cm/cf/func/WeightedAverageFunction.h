#ifndef WEIGHTED_AVERAGE_FUNCTION_H
#define WEIGHTED_AVERAGE_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include "ScoredFunction.h"
#include "Any.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

/**
@brief WeightedAverageFunction calculates the weighted average value.

WeightedAverageFunction has the following feature:
- generate(): return the weighted average.
- record(): record values into the memory.
- update(): update the weighted average value.

ADEF supports many kinds of WeightedAverageFunction:
- WeightedAverageFunction.

@par The configuration
WeightedAverageFunction has extra configurations:
- member
    - name: "object_size"
    - value: <tt>unsigned int</tt>
- member
    - name: "initial_value"
    - value: number configuration
             depends on WeightedAverageFunction::Object.
.
See setup() for the details.
*/
class WeightedAverageFunction : public ScoredFunction<double>
{
public:

    using T = double;
/// @copydoc Function::Object
    using Object = typename Function<T>::Object;
/// @copydoc ScoredFunction::Score
    using Score = typename ScoredFunction<T>::Score;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<WeightedAverageFunction> clone() const
    {
        return std::dynamic_pointer_cast<WeightedAverageFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is the WeightedAverageFunction and
has the following configuration:
- scoring_function: SuccessScoringFunction
- object_size: 50
- initial_value: 0.5
.
its configuration should be
- JSON configuration
@code
"SomeThing" : {
    "classname" : WeightedAverageFunction,
    "scoring_function" : {
        "classname" : "SuccessScoringFunction"
    },
    "object_size" : 50,
    "initial_value" : 0.5
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        ScoredFunction<T>::setup(config, pm);

        object_size_ = config.get_uint_value("object_size");
        valued_objects_.resize(object_size_);

        valued_object_counter_ = 0;
        weighted_average_ = config.get_double_value("initial_value");
    }

    Object generate() override
    {
        return weighted_average_;
    }

    bool record(const std::vector<Any>& params,
                const std::string& name = "") override
    {
        return true;
    }

    bool record(const std::vector<Any>& params,
                std::shared_ptr<const Individual> parent,
                std::shared_ptr<const Individual> offspring,
                const std::string& name = "") override
    {
        auto& valued_object = valued_objects_.at(valued_object_counter_);

        // only one param
        valued_object.object_ = CO::create(any_cast<Object>(params.front()));

        valued_object.score_ =
                scoring_function_->calculate_score(parent, offspring);

        valued_object_counter_++;
        if (valued_object_counter_ >= object_size_) {
            valued_object_counter_ = 0;
        }
        return true;
    }

    void update() override
    {
        Score sum_score = 0;
        for (auto&& valued_object : valued_objects_) {
            sum_score += valued_object.score_;
        }

        if (sum_score < std::numeric_limits<Score>::epsilon()) {
            weighted_average_ = 0;
        }
        else {
            weighted_average_ = 0;
            for (auto&& valued_object : valued_objects_) {
                weighted_average_ += valued_object.score_ / sum_score *
                                     valued_object.object_.object;
            }
        }
    }

    unsigned int number_of_parameters() const override
    {
        return 1;
    }

private:

/// The value of weighted average.
    Object weighted_average_;
/// The size of valued object.
    unsigned int object_size_;

/// The type of the encapsulated object.
    using CO = ControlledObject<Object>;

/// ValuedObject contains informations of the object including its score.
    struct ValuedObject {

        Score score_;  ///< The score of the object.
        CO object_;    ///< The object.
    };
/// The counter of the valued object.
    unsigned int valued_object_counter_;
/// The list of valued objects.
    std::vector<ValuedObject> valued_objects_;

    using ScoredFunction<T>::scoring_function_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<WeightedAverageFunction>(*this);
    }
};

}

#endif // WEIGHTED_AVERAGE_FUNCTION_H
