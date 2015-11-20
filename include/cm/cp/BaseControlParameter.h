#ifndef BASE_CONTROL_PARAMETER_H
#define BASE_CONTROL_PARAMETER_H

#include <memory>
#include "Prototype.h"

namespace adef {

/**
@brief BaseControlParameter defines interfaces of all ControlParameter.
*/
class BaseControlParameter : public Prototype
{
public:

    virtual ~BaseControlParameter() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<BaseControlParameter> clone() const
    {
        return std::dynamic_pointer_cast<BaseControlParameter>(clone_impl());
    }

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // BASE_CONTROL_PARAMETER_H
