#ifndef PROTOTYPE_MANAGER_H
#define PROTOTYPE_MANAGER_H

#include <map>
#include <string>
#include <memory>

namespace adef {

class Prototype;
class Configuration;

/**
@brief PrototypeManager implements the simple mechanism of C++ reflection.

PrototypeManager manages name-pointer pairs to create a class
pointer from the registered name.

@sa Prototype
*/
class PrototypeManager
{
public:

/**
@brief Register a class by the name.

@param name The class name to register.
@param type The class pointer to register.
*/
    void register_type(const std::string& name,
                       std::shared_ptr<Prototype> type);

/**
@brief Create a class pointer according to the registered name.

@param name The registered name of class.
@return A pointer to specific class.
*/
    std::shared_ptr<Prototype> make_type(const std::string& name) const;

/**
@brief Create a class pointer according to the registered name.
@tparam T The type to convert.
@sa make_type(name)
*/
    template<typename T>
    std::shared_ptr<T> make_type(const std::string& name) const
    {
        return std::dynamic_pointer_cast<T>(make_type(name));
    }

private:

/**
@brief The class name-pointer pairs.
*/
    std::map<std::string, std::shared_ptr<Prototype>> table_of_type_;

};

/**
@brief Create and set up a class by specifying the name
from the configuration and manager.

@param name The name of object.
@param config The Configuration which contains the name and data to set up the class.
@param pm The PrototypeManager to make the class.
*/
std::shared_ptr<Prototype> make_and_setup_type(const std::string& name,
                                               const Configuration& config,
                                               const PrototypeManager& pm);

/**
@brief Create and set up a class by specifying the name
from the configuration and manager.

@sa make_and_setup_type(class_name, config, pm)
*/
template<typename T>
std::shared_ptr<T> make_and_setup_type(const std::string& name,
                                       const Configuration& config,
                                       const PrototypeManager& pm)
{
    return std::dynamic_pointer_cast<T>(make_and_setup_type(name,
                                                            config,
                                                            pm));
}

/**
@brief Create and set up a class without specifying the name
from the configuration and manager.

@param config The Configuration which contains data to set up the class.
@param pm The PrototypeManager to make the class.
*/
std::shared_ptr<Prototype> make_and_setup_type(const Configuration& config,
                                               const PrototypeManager& pm);

/**
@brief Create and set up a class without specifying the name
from the configuration and manager.

@sa make_and_setup_type(config, pm)
*/
template<typename T>
std::shared_ptr<T> make_and_setup_type(const Configuration& config,
                                       const PrototypeManager& pm)
{
    return std::dynamic_pointer_cast<T>(make_and_setup_type(config,
                                                            pm));
}

}

#endif

