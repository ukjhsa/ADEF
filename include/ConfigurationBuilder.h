#ifndef CONFIGURATION_BUILDER_H
#define CONFIGURATION_BUILDER_H

#include <memory>
#include <istream>
#include <string>

namespace adef {

class ConfigurationData;

/**
@brief ConfigurationBuilder is the abstract base class of
creating the configuration data.

@sa Configuration, ConfigurationData.
*/
class ConfigurationBuilder
{
public:

    virtual ~ConfigurationBuilder() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ConfigurationBuilder> clone() const
    {
        return std::dynamic_pointer_cast<ConfigurationBuilder>(clone_impl());
    }

/**
@brief Load the configuration data from the input stream.
@param is The input stream.
@param config_data The configuration data to write to.
@return @c true if the loading process success, @c false otherwise.
*/
    virtual bool load_config(
             std::istream& is,
             std::shared_ptr<ConfigurationData> config_data) const = 0;

/**
@name inspection
*/
///@{
/**
@brief Check whether the configuration data belongs to the @a object.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to the @a object,
@c false otherwise.
*/
    virtual bool is_object(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Check whether the configuration data belongs to the @a array.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to the @a array,
@c false otherwise.
*/
    virtual bool is_array(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Check whether the configuration data belongs to the @c null.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to the @c null,
@c false otherwise.
*/
    virtual bool is_null(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Check whether the configuration data belongs to the @c bool.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to the @c bool,
@c false otherwise.
*/
    virtual bool is_boolean(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Check whether the configuration data belongs to the @c std::string.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to the @c std::string,
@c false otherwise.
*/
    virtual bool is_string(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Check whether the configuration data belongs to the @a number.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to the @a number,
@c false otherwise.
*/
    virtual bool is_number(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Check whether the configuration data belongs to integer number.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to integer number,
@c false otherwise.
*/
    virtual bool is_number_integer(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Check whether the configuration data belongs to floating-pointer number.
@param config_data The configuration data to check.
@return @c true if the configuration data belongs to floating-point number,
@c false otherwise.
*/
    virtual bool is_number_floating_point(
            std::shared_ptr<const ConfigurationData> config_data) const = 0;
///@}

/**
@name object operators
*/
///@{
/**
@brief Return the configuration data of the member.
@param member_name The name of the member to access.
@param config_data The configuration data to access.
*/
    virtual std::shared_ptr<ConfigurationData> get_config_data(
        const std::string& member_name,
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
///@}

/**
@name array operators
*/
///@{
/**
@brief Return the number of elements of the configuration data.
@param config_data The configuration data to access.
*/
    virtual unsigned int get_array_size(
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Return the configuration data of the element.
@param index The index of the element to access.
@param config_data The configuration data to access.
*/
    virtual std::shared_ptr<ConfigurationData> get_config_data(
        unsigned int index,
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
///@}

/**
@name value operators
*/
///@{
/**
@brief Get the @c bool of the configuration data.
@param config_data The configuration data to access.
*/
    virtual bool get_bool_value(
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Get the @c std::string of the configuration data.
@param config_data The configuration data to access.
*/
    virtual std::string get_string_value(
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Get the @c int of the configuration data.
@param config_data The configuration data to access.
*/
    virtual int get_int_value(
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Get the <tt>unsigned int</tt> of the configuration data.
@param config_data The configuration data to access.
*/
    virtual unsigned int get_uint_value(
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
/**
@brief Get the @c double of the configuration data.
@param config_data The configuration data to access.
*/
    virtual double get_double_value(
        std::shared_ptr<const ConfigurationData> config_data) const = 0;
///@}

private:

/**
@brief Clone the current class via virtual copy constructor.
*/
    virtual std::shared_ptr<ConfigurationBuilder> clone_impl() const = 0;
};

}

#endif // CONFIGURATION_BUILDER_H
