#ifndef CONTROLLED_OBJECT_H
#define CONTROLLED_OBJECT_H

#include <memory>
#include <type_traits>
#include "Prototype.h"
#include "PrototypeManager.h"
#include "Configuration.h"

namespace adef {

/// http://stackoverflow.com/a/26916426/2214727
template<typename T>
struct is_shared_ptr_helper : std::false_type {};
template<typename T>
struct is_shared_ptr_helper<std::shared_ptr<T>> : std::true_type {};
template<typename T>
struct is_shared_ptr : is_shared_ptr_helper<typename std::decay<T>::type> {};

/// http://stackoverflow.com/a/7064165/2214727
template<typename T>
struct unsupported_type : std::false_type {};

/**
@defgroup ControlledObject The controlled object
@brief ControlledObject encapsulates the object.

ControlledObject encapsulates the object for the use of
creating and copying an object.

It supports the following types @a T:
- @a T is a non-pointer and non-<tt>std::shared_ptr</tt> to
arithmetic type or a class does @a NOT inherit Prototype.
    - e.g., ControlledObject\<double>, ControlledObject\<std::string>.
- @a T is a @c std::shared_ptr to an abstract class derived from Prototype.
    - e.g., ControlledObject\<std::shared_ptr\<RealFunction>>.
- @a T is a non-pointer or @c std::shared_ptr to
a concrete class derived from Prototype.
    - e.g., ControlledObject\<RealConstantFunction>.

The supported types listed below:
Type \\ Kind  | T | T* | @c std::shared_ptr\<T> |
------------- |:-:|:--:|:---------------------:|
@c int, @c double, @c std::string, etc.  | supports | none | none |
abstract class derived from Function<br>e.g.,@c Function\<int>  | none  | none | supports |
concrete class derived from Function<br>e.g.,@c ConstantFunction\<int>  | supports | none | supports |
@{
*/

/**
@brief ControlledObject template declaration.
@tparam T The type of the controlled object.
@tparam Enable The use of template specialization.
@sa @ref ControlledObject.
*/
template<typename T, typename Enable = void>
struct ControlledObject;

/**
@brief ControlledObject template specialization for
non-pointer and non-<tt>std::shared_ptr</tt> to arithmetic type or a class
excluded Prototype-based.
@tparam T The type of the object.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<T,
                typename std::enable_if<
                            !std::is_pointer<T>::value &&
                            !is_shared_ptr<T>::value &&
                            !std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
/**
@brief The type of the object.
*/
    using Object = T;
/**
@brief The object.
*/
    Object object;
/**
@brief Create a ControlledObject from the configuration file.
@param config The Configuration to configure the object.
@param pm The PrototypeManager to make the object.
*/
    static ControlledObject<Object> create(const Configuration& config,
                                           const PrototypeManager& pm)
    {
        ControlledObject<Object> c;
        c.object = config.get_value<Object>();
        return c;
    }
/**
@brief Create a ControlledObject from an object.
@param object The object to be controlled.
*/
    static ControlledObject<Object> create(const Object& object)
    {
        ControlledObject<Object> c;
        c.object = object;
        return c;
    }
};
/**
@brief ControlledObject template specialization for unsupported type.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<T*,
                typename std::enable_if<
                            !std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
    static_assert(unsupported_type<T>::value,
                  "The template specialization is unsupported.");
};
/**
@brief ControlledObject template specialization for unsupported type.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<std::shared_ptr<T>,
                typename std::enable_if<
                            !std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
    static_assert(unsupported_type<T>::value,
                  "The template specialization is unsupported.");
};

/**
@brief ControlledObject template specialization for unsupported type.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<T,
                typename std::enable_if<
                            std::is_abstract<T>::value &&
                            std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
    static_assert(unsupported_type<T>::value,
                  "The template specialization is unsupported.");
};
/**
@brief ControlledObject template specialization for unsupported type.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<T*,
                typename std::enable_if<
                            std::is_abstract<T>::value &&
                            std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
    static_assert(unsupported_type<T>::value,
                  "The template specialization is unsupported.");
};

/**
@brief ControlledObject template specialization for
@c std::shared_ptr to a class derived from Prototype.
@tparam T The type of the object.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<std::shared_ptr<T>,
                typename std::enable_if<
                            std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
/**
@brief The type of the abstract class of the object.
*/
    using Type = T;
/**
@brief The type of the object.
*/
    using Object = std::shared_ptr<T>;
/**
@brief The controlled object.
*/
    Object object;

    ControlledObject() = default;
/**
@brief Construct a ControlledObject from another one.

The object is deep copied.
*/
    ControlledObject(const ControlledObject& rhs)
    {
        if (rhs.object) { object = rhs.object->clone(); }
    }
/**
@sa ControlledObject(const ControlledObject& rhs)
*/
    ControlledObject& operator=(const ControlledObject& rhs)
    {
        ControlledObject temp(rhs);
        std::swap(object, temp.object);
        return *this;
    }
/**
@brief Create a ControlledObject from the configuration file.
@param config The Configuration to configure the object.
@param pm The PrototypeManager to make the object.
*/
    static ControlledObject<Object> create(const Configuration& config,
                                           const PrototypeManager& pm)
    {
        ControlledObject<Object> c;
        c.object = make_and_setup_type<Type>(config, pm);
        return c;
    }
/**
@brief Create a ControlledObject from an object.
@param object The object to be controlled.
*/
    static ControlledObject<Object> create(const Object& object)
    {
        ControlledObject<Object> c;
        c.object = object->clone();
        return c;
    }
/**
@overload
*/
    static ControlledObject<Object> create(const Type& object)
    {
        ControlledObject<Object> c;
        c.object = object.clone();
        return c;
    }
};

/**
@brief ControlledObject template specialization for
non-pointer and non-<tt>std::shared_ptr</tt> to a concrete class
derived from Prototype.
@tparam T The type of the object.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<T,
                typename std::enable_if<
                            !std::is_abstract<T>::value &&
                            std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
/**
@brief The type of the object.
*/
    using Object = T;
/**
@brief The controlled object.
*/
    Object object;

    ControlledObject() = default;
/**
@brief Construct a ControlledObject from another one.

The controlled object is deep copied.
*/
    ControlledObject(const ControlledObject& rhs) :
        object(*(rhs.object.clone()))
    {
    }
/**
@sa ControlledObject(const ControlledObject& rhs)
*/
    ControlledObject& operator=(const ControlledObject& rhs)
    {
        ControlledObject temp(rhs);
        std::swap(object, temp.object);
        return *this;
    }
/**
@brief Create a ControlledObject from the configuration file.
@param config The Configuration to configure the object.
@param pm The PrototypeManager to make the object.
*/
    static ControlledObject<Object> create(const Configuration& config,
                                           const PrototypeManager& pm)
    {
        ControlledObject<Object> c;
        c.object = make_and_setup_type<Object>(config, pm);
        return c;
    }
/**
@brief Create a ControlledObject from an object.
@param object The object to be controlled.
*/
    static ControlledObject<Object> create(const Object& object)
    {
        ControlledObject<Object> c;
        c.object = *(object.clone());
        return c;
    }
};
/**
@brief ControlledObject template specialization for unsupported type.
@sa @ref ControlledObject.
*/
template<typename T>
struct ControlledObject<T*,
                typename std::enable_if<
                            !std::is_abstract<T>::value &&
                            std::is_convertible<T*, Prototype*>::value
                                        >::type
                        >
{
    static_assert(unsupported_type<T>::value,
                  "The template specialization is unsupported.");
};

/**
@}
*/

}

#endif // CONTROLLED_OBJECT_H
