#ifndef BASE_FUNCTION_H
#define BASE_FUNCTION_H

#include <memory>
#include <vector>
#include <string>
#include <any>
#include "Prototype.h"

namespace adef {

class Repository;
class Individual;
class Random;

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

    BaseFunction();
    BaseFunction(const BaseFunction& rhs);
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
    virtual void init(std::shared_ptr<Repository> repos);

/**
@brief Record parameter into the given formula.
@param params Input parameter to be record.
@param name The name of the child component to be record.
@return @c true if the record success, otherwise @c false.
*/
    virtual bool record(const std::vector<std::any>& params,
                        const std::string& name = "") = 0;
/**
@brief Record parameter into the given formula.
@param params Input parameter to be record.
@param parent The parent individual.
@param offspring The offspring individual.
@param name The name of the child component to be record.
@return @c true if the record success, otherwise @c false.
*/
    virtual bool record(const std::vector<std::any>& params,
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
    void add_function(BaseFunctionPtr function);
/**
@brief Return the component of the current composite by its name.
@param name The name of the component.
@return The component to get or @c nullptr if no found.
*/
    BaseFunctionPtr get_function(const std::string& name) const;
/**
@brief Return all components of the current composite.
*/
    BaseFunctionPtrList get_all_functions() const;

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
