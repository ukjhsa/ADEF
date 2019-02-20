#ifndef NON_INFO_CONTROL_SELECTION_H
#define NON_INFO_CONTROL_SELECTION_H

#include <memory>
#include "ControlSelection.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class BaseControlParameter;
class BaseFunction;

/**
@brief NonInfoControlSelection checks nothing.

@par The configuration
NonInfoControlSelection has no extra configurations.@n
See setup() for the details.
*/
class NonInfoControlSelection : public ControlSelection
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<NonInfoControlSelection> clone() const
    {
        return std::dynamic_pointer_cast<NonInfoControlSelection>(clone_impl());
    }
/**
@brief Set up the internal states.

NonInfoControlSelection's configuration should be
- JSON configuration
@code
"ControlSelection": {
    "classname" : "NonInfoControlSelection"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override;

    void select(std::shared_ptr<Repository> repos,
                std::shared_ptr<BaseControlParameter> parameter,
                std::shared_ptr<BaseFunction> function) const override;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<NonInfoControlSelection>(*this);
    }
};

}

#endif // NON_INFO_CONTROL_SELECTION_H
