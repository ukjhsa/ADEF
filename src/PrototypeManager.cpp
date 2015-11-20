#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include "PrototypeManager.h"
#include "Prototype.h"
#include "Configuration.h"

namespace adef {

void PrototypeManager::register_type(const std::string& name,
                                     std::shared_ptr<Prototype> type)
{
    table_of_type_[name] = type->clone();
}

std::shared_ptr<Prototype> PrototypeManager::make_type(const std::string& name) const
{
    auto it = table_of_type_.find(name);
    if (it != table_of_type_.end()) {
        return it->second->clone();
    }
    throw std::logic_error("PrototypeManager does not find the type: " + name);
    return nullptr;
}

std::shared_ptr<Prototype> make_and_setup_type(const std::string& name,
                                               const Configuration& config,
                                               const PrototypeManager& pm)
{
    auto object_config = config.get_config(name);
    return make_and_setup_type(object_config, pm);
}

std::shared_ptr<Prototype> make_and_setup_type(const Configuration& config,
                                               const PrototypeManager& pm)
{
    std::string classname = config.get_string_value("classname");
    auto object = pm.make_type(classname);
    object->setup(config, pm);
    return object;
}

}
