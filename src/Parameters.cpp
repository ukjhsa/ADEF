#include <memory>
#include <string>
#include <map>
#include "Parameters.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"

namespace adef {

Parameters::Parameters(const Parameters& rhs)
{
    for (auto&& kv : rhs.params_) {
        if (kv.second) {
            params_[kv.first] = kv.second->clone();
        }
    }
}

void Parameters::setup(const Configuration& config, const PrototypeManager& pm)
{
}

void Parameters::init(std::shared_ptr<Repository> repos)
{
}

void Parameters::store_impl(const std::string& name,
                            std::shared_ptr<BaseParameter> param)
{
    params_[name] = param;
}

std::shared_ptr<Parameters::BaseParameter> Parameters::take_out_impl(const std::string& name) const
{
    auto search = params_.find(name);
    if (search != params_.end()) {
        return search->second;
    }
    return nullptr;
}

}
