#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <memory>
#include <type_traits>

namespace adef {

class ConfigurationBuilder;
class ConfigurationData;

/**
@brief Configuration provides interfaces to access configuration data.

There are three kinds of the configuration data:
- @a object : It consists of members.
    - member: name-value pair.@n
      name is @c string and value is @a value accessed through the name.
- @a array : It consists of elements.
    - elements: @a value accessed through the ordered index.
- @a value : It can be a @c null, @c true, @c false, @c string,
@a number (including @c int, <tt>unsigned int</tt>, and @c double),
@a object or @a array.

Configuration use the Builder pattern to create configuration data.
It generates the Concrete Builder when it loads a configuration file,
then it use the builder to create configuration data.@n
See the
<a href="https://en.wikipedia.org/wiki/Builder_pattern">Builder pattern</a>

@sa ConfigurationBuilder, ConfigurationData.
*/
class Configuration
{
public:

    Configuration() = default;
/**
@brief Construct a Configuration by another one.

Note that the configuration data is deep copied,
but the builder is shadow copied.
*/
    Configuration(const Configuration& rhs);
    ~Configuration() = default;

/**
@brief Load the configuration data from the file.
@return @c true if the loading process success, @c false otherwise.
*/
    bool load_config(const std::string& filename);

/**
@name inspection
*/
///@{
/**
@brief Check whether the configuration data belongs to the @a object.
@return @c true if the configuration data belongs to the @a object,
@c false otherwise.
*/
    bool is_object() const;
/**
@brief Check whether the configuration data belongs to the @a array.
@return @c true if the configuration data belongs to the @a array,
@c false otherwise.
*/
    bool is_array() const;
/**
@brief Check whether the configuration data belongs to the @c null.
@return @c true if the configuration data belongs to the @c null,
@c false otherwise.
*/
    bool is_null() const;
/**
@brief Check whether the configuration data belongs to the @c bool.
@return @c true if the configuration data belongs to the @c bool,
@c false otherwise.
*/
    bool is_boolean() const;
/**
@brief Check whether the configuration data belongs to the @c std::string.
@return @c true if the configuration data belongs to the @c std::string,
@c false otherwise.
*/
    bool is_string() const;
/**
@brief Check whether the configuration data belongs to the @a number.
@return @c true if the configuration data belongs to the @a number,
@c false otherwise.
*/
    bool is_number() const;
/**
@brief Check whether the configuration data belongs to integer number.
@return @c true if the configuration data belongs to integer number,
@c false otherwise.
*/
    bool is_number_integer() const;
/**
@brief Check whether the configuration data belongs to floating-point number.
@return @c true if the configuration data belongs to floating-point number,
@c false otherwise.
*/
    bool is_number_floating_point() const;
///@}

/**
@name object operators
*/
///@{
/**
@brief Access the @a value of the member.
*/
    Configuration get_config(const std::string& member_name) const;
/**
@brief Get the @c bool from the @a value of the member.

@exception std::domain_error configuration is not @c bool.
*/
    bool get_bool_value(const std::string& member_name) const;
/**
@brief Get the @c std::string from the @a value of the member.

@exception std::domain_error configuration is not @c std::string.
*/
    std::string get_string_value(const std::string& member_name) const;
/**
@brief Get the @c int from the @a value of the member.

@exception std::domain_error configuration is not @c int.
*/
    int get_int_value(const std::string& member_name) const;
/**
@brief Get the <tt>unsigned int</tt> from the @a value of the member.

@exception std::domain_error configuration is not <tt>unsigned int</tt>.
*/
    unsigned int get_uint_value(const std::string& member_name) const;
/**
@brief Get the @c double from the @a value of the member.

@exception std::domain_error configuration is not @c double.
*/
    double get_double_value(const std::string& member_name) const;
///@}

/**
@name array operators
*/
///@{
/**
@brief Return the number of elements of the @a array.
*/
    unsigned int get_array_size() const;
/**
@brief Access the @a value of the element.
*/
    Configuration get_config(unsigned int index) const;
/**
@brief Get the @c bool from the @a value of the element.
*/
    bool get_bool_value(unsigned int index) const;
/**
@brief Get the @c std::string from the @a value of the element.
*/
    std::string get_string_value(unsigned int index) const;
/**
@brief Get the @c int from the @a value of the element.
*/
    int get_int_value(unsigned int index) const;
/**
@brief Get the <tt>unsigned int</tt> from the @a value of the element.
*/
    unsigned int get_uint_value(unsigned int index) const;
/**
@brief Get the @c double from the @a value of the element.
*/
    double get_double_value(unsigned int index) const;
///@}

/**
@name value operators
*/
///@{
/**
@brief Get the @c bool.

@exception std::domain_error configuration is not @c bool.
*/
    bool get_bool_value() const;

/**
@brief Get the @c std::string.

@exception std::domain_error configuration is not @c std::string.
*/
    std::string get_string_value() const;
/**
@brief Get the @c int.

@exception std::domain_error configuration is not @c int.
*/
    int get_int_value() const;
/**
@brief Get the <tt>unsigned int</tt>.

@exception std::domain_error configuration is not <tt>unsigned int</tt>.
*/
    unsigned int get_uint_value() const;
/**
@brief Get the @c double.

@exception std::domain_error configuration is not @c double.
*/
    double get_double_value() const;
/**
@brief Get the @c bool.
@tparam T The type of returning value.

@exception std::domain_error configuration is not @c bool.
*/
    template<typename T,
             std::enable_if_t<std::is_same<T, bool>::value>* = nullptr
             >
    T get_value() const
    {
        return get_bool_value();
    }
/**
@brief Get the @c std::string.
@tparam T The type of returning value.

@exception std::domain_error configuration is not @c std::string.
*/
    template<typename T,
             std::enable_if_t<std::is_same<T, std::string>::value>* = nullptr
             >
    T get_value() const
    {
        return get_string_value();
    }
/**
@brief Get the @c int.
@tparam T The type of returning value.

@exception std::domain_error configuration is not @c int.
*/
    template<typename T,
             std::enable_if_t<std::is_same<T, int>::value>* = nullptr
             >
    T get_value() const
    {
        return get_int_value();
    }
/**
@brief Get the <tt>unsigned int</tt>.
@tparam T The type of returning value.

@exception std::domain_error configuration is not <tt>unsigned int</tt>.
*/
    template<typename T,
             std::enable_if_t<std::is_same<T, unsigned int>::value>* = nullptr
             >
    T get_value() const
    {
        return get_uint_value();
    }
/**
@brief Get the @c double.
@tparam T The type of returning value.

@exception std::domain_error configuration is not @c double.
*/
    template<typename T,
             std::enable_if_t<std::is_same<T, double>::value>* = nullptr
             >
    T get_value() const
    {
        return get_double_value();
    }
///@}

/**
@sa Configuration(const Configuration& rhs)
*/
    Configuration& operator=(const Configuration& rhs);

protected:

private:

/**
@brief The builder to construct the configuration data.
*/
    std::shared_ptr<ConfigurationBuilder> builder_;
/**
@brief The configuration data.
*/
    std::shared_ptr<ConfigurationData> config_data_;

/**
@brief Clone a new Configuration except the configuration data.

Note that this function shadow copies the builder,
but the configuration data does NOT copy.

@return The same Configuration except the configuration data.
*/
    Configuration empty_clone() const;
};

}

#endif
