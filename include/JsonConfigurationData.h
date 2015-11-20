#ifndef JSON_CONFIGURATION_DATA_H
#define JSON_CONFIGURATION_DATA_H

#include "ConfigurationData.h"
#include "json.hpp"

namespace adef {

/**
@brief JsonConfigurationData stores configuration data in JSON format.
*/
class JsonConfigurationData : public ConfigurationData
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<JsonConfigurationData> clone() const
    {
        return std::static_pointer_cast<JsonConfigurationData>(clone_impl());
    }

/// The JSON value.
    nlohmann::json data;

private:

    std::shared_ptr<ConfigurationData> clone_impl() const override
    {
        return std::make_shared<JsonConfigurationData>(*this);
    }
};

}

#endif // JSON_CONFIGURATION_DATA_H
