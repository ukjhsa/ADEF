#ifndef JSON_CONFIGURATION_BUILDER_H
#define JSON_CONFIGURATION_BUILDER_H

#include <memory>
#include <istream>
#include <string>
#include "ConfigurationBuilder.h"

namespace adef {

/**
@brief JsonConfigurationBuilder creates the configuration data
in JSON format.
*/
class JsonConfigurationBuilder : public ConfigurationBuilder
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<JsonConfigurationBuilder> clone() const
    {
        return std::dynamic_pointer_cast<JsonConfigurationBuilder>(clone_impl());
    }

    bool load_config(
         std::istream& is,
         std::shared_ptr<ConfigurationData> config_data) const override;

/*
    inspection
*/

    bool is_object(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    bool is_array(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    bool is_null(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    bool is_boolean(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    bool is_string(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    bool is_number(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    bool is_number_integer(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    bool is_number_floating_point(
        std::shared_ptr<const ConfigurationData> config_data) const override;

/*
    Object
*/
    std::shared_ptr<ConfigurationData> get_config_data(
        const std::string& member_name,
        std::shared_ptr<const ConfigurationData> config_data) const override;

/*
    array
*/
    unsigned int get_array_size(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    std::shared_ptr<ConfigurationData> get_config_data(
        unsigned int index,
        std::shared_ptr<const ConfigurationData> config_data) const override;

/*
    value
*/
    bool get_bool_value(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    std::string get_string_value(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    int get_int_value(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    unsigned int get_uint_value(
        std::shared_ptr<const ConfigurationData> config_data) const override;
    double get_double_value(
        std::shared_ptr<const ConfigurationData> config_data) const override;

private:

    std::shared_ptr<ConfigurationBuilder> clone_impl() const override
    {
        return std::make_shared<JsonConfigurationBuilder>(*this);
    }
};

}

#endif // JSON_CONFIGURATION_BUILDER_H
