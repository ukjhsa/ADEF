#ifndef CONFIGURATION_DATA_H
#define CONFIGURATION_DATA_H

#include <memory>

namespace adef {

/**
@brief ConfigurationData is the abstract base class of
storing the configuration data.

It created by ConfigurationBuilder through Configuration.

@sa Configuration, ConfigurationBuilder.
*/
class ConfigurationData
{
public:

    virtual ~ConfigurationData() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ConfigurationData> clone() const
    {
        return std::static_pointer_cast<ConfigurationData>(clone_impl());
    }

private:

/**
@brief Clone the current class via virtual copy constructor.
*/
    virtual std::shared_ptr<ConfigurationData> clone_impl() const = 0;
};

}

#endif // CONFIGURATION_DATA_H
