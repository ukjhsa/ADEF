#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <memory>
#include <vector>
#include <ostream>
#include <cstddef>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Problem;

/**
@brief Individual contains decision variables, objective values,
and fitness value.

The data structure of the internal storage are invisible to other classes.
The way to access them is through accessing a value in each dimension.

@par The configuration
Individual has no extra configurations.@n
See setup() for the details.
*/
class Individual : public Prototype, public EvolutionaryState
{
public:

/// The type of decision variables.
    using VariableType = double;
/// The type of objective values.
    using ObjectiveType = double;

    Individual() = default;
    Individual(const Individual& rhs) = default;
    virtual ~Individual() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Individual> clone() const
    {
        return std::dynamic_pointer_cast<Individual>(clone_impl());
    }
/**
@brief Set up the internal states.

Individual's configuration should be
- JSON configuration
@code
"Individual" : {
    "classname" : "Individual"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;
/**
@brief Initialize this state from other states.

Individual's initialization do the following things:
- Initialize the dimension of decision variables and its initial value.
- Initialize the dimension of objective variables and its initial value.
*/
    virtual void init(std::shared_ptr<Repository> repos) override;

/**
@brief Clone the current class with default state.
*/
    std::shared_ptr<Individual> empty_clone() const;

/**
@brief Check whether the current individual is bounded within the problem.
@param problem The problem which is used to check.
*/
    virtual bool is_valid(std::shared_ptr<const Problem> problem) const;
/**
@brief Check whether the value of the dimension is bounded within the problem.
@param dimension The value of the dimension to check.
@param problem The problem which is used to check.
*/
    virtual bool is_valid(std::size_t dimension,
                          std::shared_ptr<const Problem> problem) const;
/**
@brief Replace the contents to other.
*/
    void replace(std::shared_ptr<const Individual> rhs);
/**
@name Value operators
The operators of accessing values.
*/
///@{
/**
@brief Return the size of decision variables.
*/
    std::size_t dimension_of_variable() const { return variables_.size(); }
/**
@brief Access specified decision variable.
@param index The index of decision variable.
*/
    VariableType& variables(std::size_t index = 0);
/**
@brief Access specified decision variable.
@param index The index of decision variable.
*/
    const VariableType& variables(std::size_t index = 0) const;
/**
@brief Return the size of objective values.
*/
    std::size_t dimension_of_objective() const { return objectives_.size(); }
/**
@brief Access specified objective value.
@param index The index of objective value.
*/
    ObjectiveType& objectives(std::size_t index = 0);
/**
@brief Access specified objective value.
@param index The index of objective value.
*/
    const ObjectiveType& objectives(std::size_t index = 0) const;
/**
@brief Set fitness value.
*/
    void set_fitness_value(double fitness) { fitness_ = fitness; }
/**
@brief Return fitness value.
*/
    double fitness() const { return fitness_; }
///@}

/**
@name Operators
*/
///@{
/**
@sa Individual(const Individual& rhs)
*/
    Individual& operator=(const Individual& rhs);
/**
@brief Plus @c Individual and assign to the original.

The operator affects only the decision variables.
*/
    Individual& operator+=(const Individual& rhs);
/**
@brief Minus @c Individual and assign to the original.

The operator affects only the decision variables.
*/
    Individual& operator-=(const Individual& rhs);
///@}

/**
@brief Print total variables.
@param os The @c std::ostream to print to.
*/
    void print(std::ostream& os) const;

protected:

/**
@brief The decision variables.
*/
    std::vector<VariableType> variables_;
/**
@brief The objective values.
*/
    std::vector<ObjectiveType> objectives_;
/**
@brief The fitness value.
*/
    double fitness_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Individual>(*this);
    }
};

/**
@relates Individual
@name Operators
*/
///@{
/**
@brief Individual plus Individual.

The operator affects only the decision variables.
*/
Individual operator+(const Individual& lhs, const Individual& rhs);
/**
@brief Individual minus Individual.

The operator affects only the decision variables.
*/
Individual operator-(const Individual& lhs, const Individual& rhs);
/**
@brief Individual multiplied by a value.

The operator affects only the decision variables.
*/
Individual operator*(const Individual& lhs, double value);
/**
@brief Individual multiplied by a value.
@sa operator*(const Individual& rhs, double value)
*/
Individual operator*(double value, const Individual& rhs);
///@}

}

#endif
