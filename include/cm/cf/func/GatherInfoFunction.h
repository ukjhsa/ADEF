#ifndef GATHER_INFO_FUNCTION_H
#define GATHER_INFO_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include "Function.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "cm/ControlledObject.h"
#include "Individual.h"

namespace adef {

/**
@brief GatherInfoFunction is the abstract base class of
gathering informations to storage.
@tparam T The type of the object.

GatherInfoFunction has the following feature:
- generate(): return the object changed in update().
- record(): record parameters into storage.
- update(): update the object by given method of handling informations.

@par The configuration
GatherInfoFunction has extra configurations:
- member
    - name: "storage_size"
    - value: <tt>unsigned int</tt>
.
See setup() for the details.
*/
template<typename T>
class GatherInfoFunction : public Function<T>
{
public:

/// @copydoc Function::Object
    using Object = typename Function<T>::Object;

    virtual ~GatherInfoFunction() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<GatherInfoFunction> clone() const
    {
        return std::static_pointer_cast<GatherInfoFunction>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is @em Class which is derived from GatherInfoFunction
and has the following configuration:
- storage_size: 50
.
its configuration should be
- JSON configuration
@code
"SomeThing" : {
    "classname" : "Class",
    "storage_size" : 50
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override
    {
        storage_size_ = config.get_uint_value("storage_size");
    }

protected:

/// The storage size.
    unsigned int storage_size_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // GATHER_INFO_FUNCTION_H
