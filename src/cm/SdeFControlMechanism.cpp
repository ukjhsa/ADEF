#include <memory>
#include <cmath>
#include "cm/SdeFControlMechanism.h"
#include "cm/cp/ControlParameter.h"
#include "cm/cf/ControlFunction.h"
#include "cm/cf/func/Function.h"
#include "cm/cr/ControlRange.h"
#include "Repository.h"
#include "Parameters.h"

namespace adef {

SdeFControlMechanism::Object SdeFControlMechanism::generate(std::shared_ptr<Repository> repos)
{
    auto index = repos->parameters()->take_out<std::size_t>("target_index");

    if (parameter_->is_already_generated(index))
    {
        return parameter_->load(index);
    }
    else {
        auto func = std::dynamic_pointer_cast<Function<Object>>(function_->at(index));
        auto object = func->generate();
        if (!range_->is_valid(object)) {
            object = std::abs(object - std::trunc(object));
        }
        parameter_->save(object, index);
        return object;
    }
}

}
