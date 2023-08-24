#include <memory>
#include <vector>
#include <string>
#include <any>
#include <limits>
#include "cm/cf/func/WeightedAverageFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

void WeightedAverageFunction::setup(const Configuration & config, const PrototypeManager & pm)
{
    ScoredFunction<T>::setup(config, pm);

    object_size_ = config.get_uint_value("object_size");
    valued_objects_.resize(object_size_);

    valued_object_counter_ = 0;
    weighted_average_ = config.get_double_value("initial_value");
}

WeightedAverageFunction::Object WeightedAverageFunction::generate()
{
    return weighted_average_;
}

bool WeightedAverageFunction::record(const std::vector<std::any>& params, const std::string & name)
{
    return true;
}

bool WeightedAverageFunction::record(const std::vector<std::any>& params, std::shared_ptr<const Individual> parent, std::shared_ptr<const Individual> offspring, const std::string & name)
{
    auto& valued_object = valued_objects_.at(valued_object_counter_);

    // only one param
    valued_object.object_ = CO::create(std::any_cast<Object>(params.front()));

    valued_object.score_ =
        scoring_function_->calculate_score(parent, offspring);

    valued_object_counter_++;
    if (valued_object_counter_ >= object_size_) {
        valued_object_counter_ = 0;
    }
    return true;
}

void WeightedAverageFunction::update()
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

unsigned int WeightedAverageFunction::number_of_parameters() const
{
    return 1;
}

}
