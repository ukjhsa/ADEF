#ifndef BASE_CONTROL_MECHANISM_H
#define BASE_CONTROL_MECHANISM_H

#include <memory>
#include "Prototype.h"

namespace adef {

/**
@brief BaseControlMechanism defines interfaces of all ControlMechanism.
*/
class BaseControlMechanism : public Prototype
{
public:

    virtual ~BaseControlMechanism() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<BaseControlMechanism> clone() const
    {
        return std::dynamic_pointer_cast<BaseControlMechanism>(clone_impl());
    }

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // BASE_CONTROL_MECHANISM_H
