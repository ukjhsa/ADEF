#include <memory>
#include <istream>
#include <string>
#include <exception>
#include <iostream>
#include "JsonConfigurationBuilder.h"
#include "JsonConfigurationData.h"
#include "json.hpp"

using json = nlohmann::json;

namespace adef {

bool JsonConfigurationBuilder::load_config(
                   std::istream& is,
                   std::shared_ptr<ConfigurationData> config_data) const
{
    auto json_config_data =
                std::dynamic_pointer_cast<JsonConfigurationData>(config_data);
    try {
        json_config_data->data = json::parse(is);
        return true;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

/*
    for inspection
*/

bool JsonConfigurationBuilder::is_object(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_object();
    }
    return false;
}

bool JsonConfigurationBuilder::is_array(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_array();
    }
    return false;
}

bool JsonConfigurationBuilder::is_null(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_null();
    }
    return false;
}

bool JsonConfigurationBuilder::is_boolean(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_boolean();
    }
    return false;
}

bool JsonConfigurationBuilder::is_string(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_string();
    }
    return false;
}

bool JsonConfigurationBuilder::is_number(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_number();
    }
    return false;
}

bool JsonConfigurationBuilder::is_number_integer(
        std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_number_integer();
    }
    return false;
}

bool JsonConfigurationBuilder::is_number_floating_point(
        std::shared_ptr<const ConfigurationData> config_data) const
{
    if (config_data) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.is_number_float();
    }
    return false;
}

/*
    for Object
*/

std::shared_ptr<ConfigurationData> JsonConfigurationBuilder::get_config_data(
                    const std::string& member_name,
                    std::shared_ptr<const ConfigurationData> config_data) const
{
    if (is_object(config_data)) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        if (json_config_data->data.find(member_name) !=
                                            json_config_data->data.end()) {
            JsonConfigurationData new_config_data;
            new_config_data.data = json_config_data->data[member_name];
            return std::make_shared<JsonConfigurationData>(new_config_data);
        }
    }
    return std::make_shared<JsonConfigurationData>();
}

/*
    for Array
*/

unsigned int JsonConfigurationBuilder::get_array_size(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (is_array(config_data)) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
        return json_config_data->data.size();
    }
    return 0;
}

std::shared_ptr<ConfigurationData> JsonConfigurationBuilder::get_config_data(
                    unsigned int index,
                    std::shared_ptr<const ConfigurationData> config_data) const
{
    if ((is_array(config_data)) && (index < get_array_size(config_data))) {
        auto json_config_data =
            std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);

        JsonConfigurationData new_config_data;
        new_config_data.data = json_config_data->data[index];
        return std::make_shared<JsonConfigurationData>(new_config_data);
    }
    return std::make_shared<JsonConfigurationData>();
}

/*
    for Value
*/

bool JsonConfigurationBuilder::get_bool_value(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (!is_boolean(config_data)) {
        throw std::domain_error("configuration data bool does not exist.");
    }
    auto json_config_data =
        std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
    return json_config_data->data.get<bool>();
}

std::string JsonConfigurationBuilder::get_string_value(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (!is_string(config_data)) {
        throw std::domain_error("configuration data string does not exist.");
    }
    auto json_config_data =
        std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
    return json_config_data->data.get<std::string>();
}

int JsonConfigurationBuilder::get_int_value(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (!is_number(config_data)) {
        throw std::domain_error("configuration data int does not exist.");
    }
    auto json_config_data =
        std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
    return json_config_data->data.get<int>();
}

unsigned int JsonConfigurationBuilder::get_uint_value(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (!is_number(config_data)) {
        throw std::domain_error("configuration data uint does not exist.");
    }
    auto json_config_data =
        std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
    return json_config_data->data.get<unsigned int>();
}

double JsonConfigurationBuilder::get_double_value(
            std::shared_ptr<const ConfigurationData> config_data) const
{
    if (!is_number(config_data)) {
        throw std::domain_error("configuration data double does not exist.");
    }
    auto json_config_data =
        std::dynamic_pointer_cast<const JsonConfigurationData>(config_data);
    return json_config_data->data.get<double>();
}

}
