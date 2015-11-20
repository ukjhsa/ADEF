#ifndef CONTROL_SELECTION_H
#define CONTROL_SELECTION_H

#include <memory>
#include "Prototype.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class BaseControlParameter;
class BaseFunction;

/**
@brief ControlSelection is the abstract base class of
how to update internal states by the relation between parent and offspring.

It is called by ControlMechanism::select().

@par The configuration
ControlSelection has no extra configurations.@n
See setup() for the details.
*/
class ControlSelection : public Prototype
{
public:

    virtual ~ControlSelection() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ControlSelection> clone() const
    {
        return std::dynamic_pointer_cast<ControlSelection>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from ControlSelection, its configuration should be
- JSON configuration
@code
"ControlSelection": {
    "classname" : "Class"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override = 0;
/**
@brief Check whether it is successful to the offspring.
*/
    virtual void select(std::shared_ptr<Repository> repos,
                        std::shared_ptr<BaseControlParameter> parameter,
                        std::shared_ptr<BaseFunction> function) const = 0;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // CONTROL_SELECTION_H
