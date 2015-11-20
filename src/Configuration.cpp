#include <memory>
#include <string>
#include <fstream>
#include <utility>
#include "Configuration.h"
#include "JsonConfigurationBuilder.h"
#include "JsonConfigurationData.h"

namespace adef {

Configuration::Configuration(const Configuration& rhs) :
    builder_(rhs.builder_)
{
    if (rhs.config_data_) {
        config_data_ = rhs.config_data_->clone();
    }
}

bool Configuration::load_config(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
        if (filename.find(".json") == std::string::npos) {
            return false;
        }
        else {
            builder_ = std::make_shared<JsonConfigurationBuilder>();
            config_data_ = std::make_shared<JsonConfigurationData>();
            return builder_->load_config(ifs, config_data_);
        }
    }
    return false;
}

/*
    for inspection
*/

bool Configuration::is_object() const
{
    return builder_->is_object(config_data_);
}

bool Configuration::is_array() const
{
    return builder_->is_array(config_data_);
}

bool Configuration::is_null() const
{
    return builder_->is_null(config_data_);
}

bool Configuration::is_boolean() const
{
    return builder_->is_boolean(config_data_);
}

bool Configuration::is_string() const
{
    return builder_->is_string(config_data_);
}

bool Configuration::is_number() const
{
    return builder_->is_number(config_data_);
}

bool Configuration::is_number_integer() const
{
    return builder_->is_number_integer(config_data_);
}

bool Configuration::is_number_floating_point() const
{
    return builder_->is_number_floating_point(config_data_);
}

/*
    for object
*/

Configuration Configuration::get_config(const std::string& member_name) const
{
    Configuration config = empty_clone();
    config.config_data_ = builder_->get_config_data(member_name, config_data_);
    return config;
}

bool Configuration::get_bool_value(const std::string& member_name) const
{
    return get_config(member_name).get_bool_value();
}

std::string Configuration::get_string_value(
                                        const std::string& member_name) const
{
    return get_config(member_name).get_string_value();
}

int Configuration::get_int_value(const std::string& member_name) const
{
    return get_config(member_name).get_int_value();
}

unsigned int Configuration::get_uint_value(const std::string& member_name) const
{
    return get_config(member_name).get_uint_value();
}

double Configuration::get_double_value(const std::string& member_name) const
{
    return get_config(member_name).get_double_value();
}

/*
    for array
*/

unsigned int Configuration::get_array_size() const
{
    return builder_->get_array_size(config_data_);
}

Configuration Configuration::get_config(unsigned int index) const
{
    Configuration config = empty_clone();
    config.config_data_ = builder_->get_config_data(index, config_data_);
    return config;
}

bool Configuration::get_bool_value(unsigned int index) const
{
    return get_config(index).get_bool_value();
}

std::string Configuration::get_string_value(unsigned int index) const
{
    return get_config(index).get_string_value();
}

int Configuration::get_int_value(unsigned int index) const
{
    return get_config(index).get_int_value();
}

unsigned int Configuration::get_uint_value(unsigned int index) const
{
    return get_config(index).get_uint_value();
}

double Configuration::get_double_value(unsigned int index) const
{
    return get_config(index).get_double_value();
}

/*
    for value
*/

bool Configuration::get_bool_value() const
{
    return builder_->get_bool_value(config_data_);
}

std::string Configuration::get_string_value() const
{
    return builder_->get_string_value(config_data_);
}

int Configuration::get_int_value() const
{
    return builder_->get_int_value(config_data_);
}


unsigned int Configuration::get_uint_value() const
{
    return builder_->get_uint_value(config_data_);
}

double Configuration::get_double_value() const
{
    return builder_->get_double_value(config_data_);
}

Configuration& Configuration::operator=(const Configuration& rhs)
{
    Configuration temp(rhs);
    std::swap(this->config_data_, temp.config_data_);
    return *this;
}

Configuration Configuration::empty_clone() const
{
    Configuration config;
    config.builder_ = this->builder_;
    return config;
}

}
