#include <memory>
#include "cm/cf/SingleControlFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "cm/cf/func/BaseFunction.h"

namespace adef {

SingleControlFunction::SingleControlFunction(const SingleControlFunction& rhs) :
    ControlFunction(rhs),
    function_(rhs.function_ ? rhs.function_->clone() : nullptr)
{
}

void SingleControlFunction::setup(const Configuration& config, const PrototypeManager& pm)
{
    function_ = make_and_setup_type<BaseFunction>("Function", config, pm);
}

void SingleControlFunction::init(std::shared_ptr<Repository> repos)
{
    function_->init(repos);
}

}
