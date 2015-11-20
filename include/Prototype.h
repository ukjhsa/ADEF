#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <memory>

namespace adef {

class Configuration;
class PrototypeManager;

/**
@brief Prototype is the abstract base class of
those can change the implementation class dynamically
and can configure its internal states through the configuration file.

Classes derived from Prototype are registered to PrototypeManager
when calling init_adef().

@par The configuration
Prototype has extra configurations:
- member
    - name: "classname"
    - value: @c string
.
See setup() for the details.

@sa PrototypeManager
*/
class Prototype
{
public:

    virtual ~Prototype() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Prototype> clone() const
    {
        return clone_impl();
    }

/**
@brief Set up the internal states.
@param config The Configuration to configure the current class.
@param pm The PrototypeManager to make the inner class.

Classes derived from Prototype can be set up the internal states
from the configuration file by calling setup().

@par JSON configuration
If @a SomeThing is a class derived from Prototype
and has the following configuration:
- classname: ClassName
.
its configuration should be
@code
"SomeThing" : {
    "classname" : "ClassName"
}
@endcode
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) = 0;

private:

/**
@brief Clone the current class via virtual copy constructor.
*/
    virtual std::shared_ptr<Prototype> clone_impl() const = 0;
};

}

#endif

