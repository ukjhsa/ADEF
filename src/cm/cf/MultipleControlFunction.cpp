#include <memory>
#include <vector>
#include "cm/cf/MultipleControlFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "cm/cf/func/BaseFunction.h"

namespace adef {

MultipleControlFunction::MultipleControlFunction(const MultipleControlFunction& rhs) :
    ControlFunction(rhs)
{
    functions_.reserve(rhs.functions_.size());
    for (auto&& func : rhs.functions_) {
        if (func) { functions_.push_back(func->clone()); }
        else { functions_.push_back(nullptr); }
    }
}

void MultipleControlFunction::setup(const Configuration& config, const PrototypeManager& pm)
{
    auto size = config.get_uint_value("number_of_functions");
    functions_.reserve(size);

    auto function = make_and_setup_type<BaseFunction>("Function", config, pm);
    for (decltype(size) idx = 0; idx < size; ++idx) {
        functions_.push_back(function->clone());
    }
}

void MultipleControlFunction::init(std::shared_ptr<Repository> repos)
{
    for (std::size_t idx = 0; idx < functions_.size(); ++idx)
    {
        functions_[idx]->init(repos);
    }
}

std::shared_ptr<BaseFunction> MultipleControlFunction::at(std::size_t index)
{
    return functions_.at(index);
}

}
