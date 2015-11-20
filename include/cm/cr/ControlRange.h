#ifndef CONTROL_RANGE_H
#define CONTROL_RANGE_H

#include <memory>
#include <type_traits>
#include "Prototype.h"
#include "cm/ControlledObject.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "util/math_tool.h"
#include "cm/cf/func/Function.h"

namespace adef {

/**
@brief ControlRange manages the range of the object.
@tparam T The type of the object. It is arithmetic type.

ControlRange defines the following interfaces:
- is_valid(): check whether the object is in the range.

Now ADEF support many kinds of ControlRange:
- ::IntegerControlRange
- ::RealControlRange
- ::IntegerControlControlRange
- ::RealControlControlRange

@par Setting
- set_lower_bound()
- set_upper_bound()

@par The configuration
ControlRange has extra configurations:
- member
    - name: "lower_bound"
    - value: @c double
- member
    - name: "upper_bound"
    - value: @c double
.
See setup() for the details.
*/
template<typename T, typename Enable = void>
class ControlRange : public Prototype
{
public:

/// The type of the object.
    using Object = typename ControlledObject<T>::Object;

    ControlRange() = default;
    ControlRange(Object lower_bound, Object upper_bound) :
        lower_bound_(lower_bound), upper_bound_(upper_bound)
    {
    }
    ControlRange(const ControlRange& rhs) = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ControlRange> clone() const
    {
        return std::dynamic_pointer_cast<ControlRange>(clone_impl());
    }
/**
@brief Set up the internal states.

If ::RealControlRange has the following configuration:
- lower bound: 0.0
- upper bound: 1.0
.
its configuration should be
- JSON configuration
@code
"ControlRange" : {
    "classname" : "RealControlRange",
    "lower_bound" : 0.0,
    "upper_bound" : 1.0
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
        auto lower_bound_config = config.get_config("lower_bound");
        lower_bound_ = lower_bound_config.get_value<Object>();
        auto upper_bound_config = config.get_config("upper_bound");
        upper_bound_ = upper_bound_config.get_value<Object>();
    }
/**
@name Setting
*/
///@{
/**
@brief Set the lower bound
*/
    void set_lower_bound(Object lower_bound) { lower_bound_ = lower_bound; }
/**
@brief Set the upper bound
*/
    void set_upper_bound(Object upper_bound) { upper_bound_ = upper_bound; }
///@}
/**
@brief Check whether the object is in the range.
@param object The object to be checked.
@return @c true if the object is in the range, @c false otherwise
*/
    bool is_valid(const Object& object) const
    {
        if (std::is_floating_point<Object>::value) {

            return is_less_equal(lower_bound_, object) &&
                   is_less_equal(object, upper_bound_);
        }
        else {
            return lower_bound_ <= object &&
                   object <= upper_bound_;
        }
    }

private:

/// The lower bound of the object.
    Object lower_bound_;
/// The upper bound of the object.
    Object upper_bound_;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<ControlRange>(*this);
    }
};

/**
@brief ControlRange template specialization for non-arithmetic type.
@tparam T The type of the object. It is non-arithmetic type.

@par The configuration
ControlRange template specialization has no extra configurations.@n
See setup() for the details.

@sa ControlRange.
*/
template<typename T>
class ControlRange<T, std::enable_if_t<!std::is_arithmetic<T>::value>>
    : public Prototype
{
public:

/// The type of the object.
    using Object = typename ControlledObject<T>::Object;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ControlRange> clone() const
    {
        return std::dynamic_pointer_cast<ControlRange>(clone_impl());
    }
/**
@brief Set up the internal states.

If ::RealControlControlRange is used and has no extra configuration.@n
its configuration should be
- JSON configuration
@code
"ControlRange" : {
    "classname" : "RealControlControlRange"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
    }

/**
@brief Check whether the object is in the range.
@return always return @c true.
*/
    bool is_valid(const Object& object) const
    {
        return true;
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<ControlRange>(*this);
    }
};

/**
@brief IntegerControlRange is the ControlRange that
controls the integer number.
*/
using IntegerControlRange = ControlRange<int>;
/**
@brief RealControlRange is the ControlRange that
controls the real number.
*/
using RealControlRange = ControlRange<double>;
/**
@brief IntegerControlControlRange is the ControlRange
that controls the ::IntegerFunction.
*/
using IntegerControlControlRange = ControlRange<std::shared_ptr<IntegerFunction>>;
/**
@brief RealControlControlRange is the ControlRange
that controls the ::RealFunction.
*/
using RealControlControlRange = ControlRange<std::shared_ptr<RealFunction>>;

}

#endif // CONTROL_RANGE_H
