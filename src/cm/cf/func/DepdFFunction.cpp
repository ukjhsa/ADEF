#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include "cm/cf/func/DepdFFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

void DepdFFunction::setup(const Configuration & config, const PrototypeManager & pm)
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

DepdFFunction::Object DepdFFunction::generate()
{
    // avoid min_ equal to zero
    if (std::abs(min_) < std::numeric_limits<Object>::epsilon()) {
        min_ = std::numeric_limits<Object>::epsilon();
    }

    if (std::abs(max_ / min_) < 1) {
        return std::max(lower_bound_, 1 - std::abs(max_ / min_));
    }
    else {
        return std::max(lower_bound_, 1 - std::abs(min_ / max_));
    }
}

void DepdFFunction::update()
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

unsigned int DepdFFunction::number_of_parameters() const
{
    return 0;
}

}
