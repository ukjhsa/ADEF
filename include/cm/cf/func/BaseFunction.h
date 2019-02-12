#ifndef BASE_FUNCTION_H
#define BASE_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include "Prototype.h"
#include "Repository.h"
#include "Random.h"
#include "Any.h"

namespace adef {

class Individual;

/**
@brief BaseFunction defines interfaces of all Function.
*/
class BaseFunction : public Prototype
{
public:

/// The type of pointer to BaseFunction.
    using BaseFunctionPtr = std::shared_ptr<BaseFunction>;
/// The type of the list of BaseFunction::BaseFunctionPtr.
    using BaseFunctionPtrList = std::vector<BaseFunctionPtr>;

    BaseFunction() : name_("root"), functions_()
    {
    }
    BaseFunction(const BaseFunction& rhs) : Prototype(rhs), name_(rhs.name_)
    {
        functions_.reserve(rhs.functions_.size());
        for (auto&& func : rhs.functions_) {
            if (func) { functions_.push_back(func->clone()); }
            else { functions_.push_back(nullptr); }
        }
    }
    virtual ~BaseFunction() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<BaseFunction> clone() const
    {
        return std::dynamic_pointer_cast<BaseFunction>(clone_impl());
    }
/**
@brief Initialize this state from other states.
@param repos The Repository to get initialization informations.
*/
    virtual void init(std::shared_ptr<Repository> repos)
    {
        random_ = repos->random();
    }

/**
@brief Record parameter into the given formula.
@param params Input parameter to be record.
@param name The name of the child component to be record.
@return @c true if the record success, otherwise @c false.
*/
    virtual bool record(const std::vector<Any>& params,
                        const std::string& name = "") = 0;
/**
@brief Record parameter into the given formula.
@param params Input parameter to be record.
@param parent The parent individual.
@param offspring The offspring individual.
@param name The name of the child component to be record.
@return @c true if the record success, otherwise @c false.
*/
    virtual bool record(const std::vector<Any>& params,
                        std::shared_ptr<const Individual> parent,
                        std::shared_ptr<const Individual> offspring,
                        const std::string& name = "") = 0;
/**
@brief Update internal states of the given formula.

Update states in order to the next call for generate().
*/
    virtual void update() = 0;
/**
@brief Return the number of parameters to be recorded.
*/
    virtual unsigned int number_of_parameters() const = 0;
/**
@brief Set the name of the current Function.
*/
    void set_function_name(const std::string& name) { name_ = name; }
/**
@brief Return the name of the current Function.
*/
    const std::string& function_name() const { return name_; }
/**
@brief Add a component into the current composite.
*/
    void add_function(BaseFunctionPtr function)
    {
        functions_.push_back(function);
    }
/**
@brief Return the component of the current composite by its name.
@param name The name of the component.
@return The component to get or @c nullptr if no found.
*/
    BaseFunctionPtr get_function(const std::string& name) const
    {
        auto it = std::find_if(
                    functions_.begin(),
                    functions_.end(),
                    [&](const BaseFunctionPtr& target) {
                        if (target->function_name() == name) { return true; }
                        else { return false; }
                    });
        if (it != functions_.end()) {
            return *it;
        }
        else {
            return nullptr;
        }
    }
/**
@brief Return all components of the current composite.
*/
    BaseFunctionPtrList get_all_functions() const
    {
        return functions_;
    }

protected:

/// The name of the current Function.
    std::string name_;
/// The list of contained Function.
    BaseFunctionPtrList functions_;

    std::shared_ptr<Random> random_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif // BASE_FUNCTION_H
