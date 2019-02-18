#include <memory>
#include <vector>
#include <string>
#include "cm/cf/func/SdeFFunction.h"
#include "cm/ControlledObject.h"
#include "Any.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

void SdeFFunction::setup(const Configuration & config, const PrototypeManager & pm)
{
    auto rand_config = config.get_config("rand");
    auto rand = make_and_setup_type<BaseFunction>(rand_config, pm);
    rand->set_function_name("rand");
    add_function(rand);

    parameters_.resize(config.get_uint_value("number_of_parameters"));
}

SdeFFunction::Object SdeFFunction::generate()
{
    Object diff = 0;
    auto size = parameters_.size();
    for (decltype(size) idx = 1; idx < size; idx += 2) {
        diff += parameters_.at(idx) - parameters_.at(idx + 1);
    }
    return parameters_.at(0) + get_function("rand")->generate() * diff;
}

bool SdeFFunction::record(const std::vector<Any>& params, const std::string & name)
{
    if (params.size() == parameters_.size()) {
        for (decltype(params.size()) idx = 0; idx < params.size(); ++idx) {
            parameters_.at(idx) = any_cast<Object>(params.at(idx));
        }
    }
    else {
        throw std::logic_error("SdeFFunction accept wrong parameters.");
    }
    return true;
}

bool SdeFFunction::record(const std::vector<Any>& params, std::shared_ptr<const Individual> parent, std::shared_ptr<const Individual> offspring, const std::string & name)
{
    return record(params, name);
}

void SdeFFunction::update()
{
    get_function("rand")->update();
}

unsigned int SdeFFunction::number_of_parameters() const
{
    return parameters_.size();
}

}
