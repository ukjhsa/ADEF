#ifndef MEDIAN_FUNCTION_H
#define MEDIAN_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include <any>
#include <algorithm>
#include "GatherInfoFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "cm/ControlledObject.h"
#include "Individual.h"

namespace adef {

/**
@brief MedianFunction generates the median value
from gathering informations.
@tparam T The type of the object. It must be arithmetic type.

MedianFunction has the following feature:
- generate(): return the median value.
- record(): record parameters into the storage.
- update(): update the median value from storage.

ADEF supports many kinds of MedianFunction:
- IntegerMedianFunction.
- RealMedianFunction.

@par The configuration
MedianFunction has extra configurations:
- member
    - name: "initial_value"
    - value: number configuration
.
See setup() for the details.
*/
template<typename T>
class MedianFunction : public GatherInfoFunction<T>
{
    static_assert(std::is_arithmetic<T>::value,
                  "MedianFunction supports only arithmetic type");
public:

/// @copydoc GatherInfoFunction::Object
    using Object = typename GatherInfoFunction<T>::Object;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<MedianFunction> clone() const
    {
        return std::static_pointer_cast<MedianFunction>(clone_impl());
    }

/**
@brief Set up the internal states.

If @em SomeThing is the ::RealMedianFunction and
has the following configuration:
- storage_size: 50
- initial_value: 0.5
.
its configuration should be
- JSON configuration
@code
"SomeThing" : {
    "classname" : "RealMedianFunction",
    "storage_size" : 50,
    "initial_value" : 0.5
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        GatherInfoFunction<T>::setup(config, pm);

        median_ = config.get_config("initial_value").get_value<Object>();

        storage_counter_ = 0;
        storage_.resize(storage_size_);
    }

    Object generate() override
    {
        return median_;
    }

    bool record(const std::vector<std::any>& params,
                const std::string& name = "") override
    {
        for (auto&& param : params) {

            storage_.at(storage_counter_) = std::any_cast<Object>(param);
            storage_counter_++;
            if (storage_counter_ >= storage_size_) {
                storage_counter_ = 0;
                storage_.at(storage_counter_) = 0;
            }
        }
        return true;
    }

    bool record(const std::vector<std::any>& params,
                std::shared_ptr<const Individual> parent,
                std::shared_ptr<const Individual> offspring,
                const std::string& name = "") override
    {
        return record(params, name);
    }

    void update() override
    {
        auto sorted_storage = storage_;
        std::sort(sorted_storage.begin(), sorted_storage.end());

        auto size = sorted_storage.size();
        if (size % 2 == 0) {
            median_ = (sorted_storage[size/2 - 1] + sorted_storage[size/2]) / 2;
        }
        else {
            median_ = sorted_storage[size/2];
        }
    }
/**
@brief Return the number of parameters to be recorded.
@return The maximum of the number of parameters.
*/
    unsigned int number_of_parameters() const override
    {
        return storage_size_;
    }

private:

/// The median value.
    Object median_;
/// @copydoc GatherInfoFunction::storage_size_
    using GatherInfoFunction<T>::storage_size_;
/// The counter of the storage.
    unsigned int storage_counter_;
/// The storage.
    std::vector<Object> storage_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<MedianFunction>(*this);
    }
};

/**
@brief IntegerMedianFunction is the MedianFunction that
controls the integer number.
*/
using IntegerMedianFunction = MedianFunction<int>;
/**
@brief RealMedianFunction is the MedianFunction that
controls the real number.
*/
using RealMedianFunction = MedianFunction<double>;

}

#endif // MEDIAN_FUNCTION_H
