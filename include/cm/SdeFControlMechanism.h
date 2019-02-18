#ifndef SDE_F_CONTROL_MECHANISM_H
#define SDE_F_CONTROL_MECHANISM_H

#include <memory>
#include <cstddef>
#include <cmath>
#include "ControlMechanism.h"
#include "cp/ControlParameter.h"
#include "cf/ControlFunction.h"
#include "cr/ControlRange.h"
#include "Repository.h"
#include "Parameters.h"
#include "cf/func/Function.h"

namespace adef {

class Repository;

/**
@brief SdeFControlMechanism adjusts the object according to
the procedure of the F value in the SDE algorithm.

The difference between this and ControlMechanism:
- generate(): if the object is invalid, then truncate the constant part.

@par Requirement
Take out parameters from Parameters:
- type @c std::size_t and name "target_index" in
generate(), select(), and update().
.

@par The configuration
SdeFControlMechanism has no extra configurations.@n
See setup() for the details.
*/
class SdeFControlMechanism : public ControlMechanism<double>
{
public:

    using T = double;
/// The type of the object.
    using Object = typename ControlMechanism<T>::Object;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<SdeFControlMechanism> clone() const
    {
        return std::dynamic_pointer_cast<SdeFControlMechanism>(clone_impl());
    }

    Object generate(std::shared_ptr<Repository> repos) override;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<SdeFControlMechanism>(*this);
    }
};

}

#endif // SDE_F_CONTROL_MECHANISM_H
