#include <memory>
#include "cm/cs/NonInfoControlSelection.h"
#include "cm/cp/BaseControlParameter.h"
#include "cm/cf/func/BaseFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"

namespace adef {

void NonInfoControlSelection::setup(const Configuration & config, const PrototypeManager & pm)
{
}

void NonInfoControlSelection::select(std::shared_ptr<Repository> repos, std::shared_ptr<BaseControlParameter> parameter, std::shared_ptr<BaseFunction> function) const
{
}

}
