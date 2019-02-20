#include <memory>
#include <string>
#include <stdexcept>
#include "cm/cu/GenerationControlUpdate.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Parameters.h"

namespace adef {

void GenerationControlUpdate::setup(const Configuration & config, const PrototypeManager & pm)
{
}

void GenerationControlUpdate::update(std::shared_ptr<Repository> repos, std::shared_ptr<BaseControlParameter> parameter, std::shared_ptr<BaseFunction> function) const
{
    std::string name = "generation";
    auto generation = repos->parameters()->take_out<unsigned int>(name);
    auto succ = function->record({ generation }, name);
    if (!succ) {
        throw std::runtime_error(
            "No functions accept parameters \"" + name + "\" "
            "in the \"" + function->function_name() + "\"");
    }
}

}
