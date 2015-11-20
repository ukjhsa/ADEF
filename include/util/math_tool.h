#ifndef MATH_TOOL_H
#define MATH_TOOL_H

#include <cmath>
#include <limits>

namespace adef {

/// Return the value of pi
inline
double pi() { return std::atan2(0, -1); }

/// Return the value of epsilon of the type @em T
template<typename T>
constexpr T epsilon() { return std::numeric_limits<T>::epsilon(); }

/**
@brief Check whether @em lhs is less than @em rhs
@return @c true if @em lhs is less than @em rhs, @c false otherwise.
*/
inline
bool is_less(double lhs, double rhs) { return std::isless(lhs, rhs); }
/**
@brief Check whether @em lhs is greater than @em rhs
@return @c true if @em lhs is greater than @em rhs, @c false otherwise.
*/
inline
bool is_greater(double lhs, double rhs) { return std::isgreater(lhs, rhs); }
/**
@brief Check whether @em lhs is equal to @em rhs
@return @c true if @em lhs is equal to @em rhs, @c false otherwise.
*/
inline
bool is_equal(double lhs, double rhs) {
    return std::abs(lhs - rhs) < epsilon<double>();
}
/**
@brief Check whether @em lhs is less and equal to @em rhs
@return @c true if @em lhs is less and equal to @em rhs, @c false otherwise.
*/
inline
bool is_less_equal(double lhs, double rhs) {
    return is_less(lhs, rhs) || is_equal(lhs, rhs);
}
/**
@brief Check whether @em lhs is greater and equal to @em rhs
@return @c true if @em lhs is greater and equal to @em rhs, @c false otherwise.
*/
inline
bool is_greater_equal(double lhs, double rhs) {
    return is_greater(lhs, rhs) || is_equal(lhs, rhs);
}

}

#endif // MATH_TOOL_H
