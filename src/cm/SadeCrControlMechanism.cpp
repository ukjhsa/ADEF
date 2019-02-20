#include <memory>
#include "cm/SadeCrControlMechanism.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/ControlFunction.h"
#include "cm/cf/func/BaseFunction.h"
#include "cm/cs/ControlSelection.h"
#include "cm/cu/ControlUpdate.h"
#include "Repository.h"
#include "Parameters.h"

namespace adef {

void SadeCrControlMechanism::select(std::shared_ptr<Repository> repos)
{
    auto index = repos->parameters()->take_out<std::size_t>("target_index");
    auto func = function_->at(index)->get_function("mean");
    selection_->select(repos, parameter_, func);
}

void SadeCrControlMechanism::update(std::shared_ptr<Repository> repos)
{
    auto index = repos->parameters()->take_out<std::size_t>("target_index");
    auto func = function_->at(index)->get_function("mean");
    for (auto& update : updates_) {
        update->update(repos, parameter_, func);
    }

    function_->at(index)->update();
    parameter_->reset_already_generated(index);
}

}
