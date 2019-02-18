#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <random>
#include "cm/cf/func/IsadeFFunction.h"
#include "Any.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Random.h"
#include "Individual.h"

namespace adef {

void IsadeFFunction::setup(const Configuration & config, const PrototypeManager & pm)
{
    auto object_config = config.get_config("object");
    auto object = make_and_setup_type<BaseFunction>(object_config, pm);
    object->set_function_name("object");
    add_function(object);

    auto min_config = config.get_config("min");
    auto min = make_and_setup_type<BaseFunction>(min_config, pm);
    min->set_function_name("min");
    add_function(min);

    auto average_config = config.get_config("average");
    auto average = make_and_setup_type<BaseFunction>(average_config, pm);
    average->set_function_name("average");
    add_function(average);

    auto current_config = config.get_config("current");
    auto current = make_and_setup_type<BaseFunction>(current_config, pm);
    current->set_function_name("current");
    add_function(current);

    auto tau_config = config.get_config("tau");
    auto tau = make_and_setup_type<BaseFunction>(tau_config, pm);
    tau->set_function_name("tau");
    add_function(tau);

    object_ = 0;
    min_ = 0;
    average_ = 0;
    current_ = 0;
    tau_ = 0.1;
}

IsadeFFunction::Object IsadeFFunction::generate()
{
    std::mt19937 gen(random_->random());
    std::uniform_real_distribution<> uniform;
    auto random = uniform(gen);
    if (random < tau_ && current_ < average_) {
        if (std::abs(average_ - min_) < std::numeric_limits<Object>::epsilon()) {
            average_ += std::numeric_limits<Object>::epsilon();
        }
        return 0.1 + (object_ - 0.1) *
            (current_ - min_) / (average_ - min_);
    }
    else if (random < tau_ && current_ >= average_) {
        std::uniform_real_distribution<> uniform(0.1, 1);
        return uniform(gen);
    }
    else {
        return object_;
    }
}

void IsadeFFunction::update()
{
    auto object = get_function("object");
    object->update();
    object_ = object->generate();

    auto min = get_function("min");
    min->update();
    min_ = min->generate();

    auto average = get_function("average");
    average->update();
    average_ = average->generate();

    auto current = get_function("current");
    current->update();
    current_ = current->generate();

    auto tau = get_function("tau");
    tau->update();
    tau_ = tau->generate();
}

unsigned int IsadeFFunction::number_of_parameters() const
{
    return 0;
}

}
