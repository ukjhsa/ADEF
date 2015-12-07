#ifndef PROBLEM_H
#define PROBLEM_H

#include <memory>
#include <string>
#include <vector>
#include <cstddef>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Individual;

/**
@brief Problem is the abstract base class of all problems to solve.

The problem can be a test function or a real application on real number space.

@par The configuration
Problem has extra configurations:
- member (optional)
    - name: "kind"
    - value: "min" or "max"
- member (optional)
    - name: "dimension_of_decision_space"
    - value: <tt>unsigned int</tt>
- member (optional)
    - name: "lower_bound_of_decision_space"
    - value: @c double
- member (optional)
    - name: "upper_bound_of_decision_space"
    - value: @c double
- member (optional)
    - name: "dimension_of_objective_space"
    - value: <tt>unsigned int</tt>
- member (optional)
    - name: "lower_bound_of_objective_space"
    - value: @c double
- member (optional)
    - name: "upper_bound_of_objective_space"
    - value: @c double
- member (optional)
    - name: "optimal_solution"
    - value: @c double
.
See setup() for the details.
*/
class Problem : public Prototype, public EvolutionaryState
{
public:

/// The type of the value what this problem deals with.
    using Object = double;

/// The kinds of problems.
    enum ProblemKind
    {
        MIN,  ///< The minimization problem
        MAX   ///< The maximization problem
    };

/**
@brief Construct a Problem with the name.
*/
    Problem(const std::string& name);
    Problem(const Problem& rhs) = default;
    virtual ~Problem() = default;
    Problem& operator=(const Problem& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Problem> clone() const
    {
        return std::dynamic_pointer_cast<Problem>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em Class is derived from Problem and has the following configuration:
- kind: min
- dimension_of_decision_space: 30
- lower_bound_of_decision_space: -100
- upper_bound_of_decision_space: 100
- dimension_of_objective_space: 1
- optimal_solution: 0
.
its configuration should be
- JSON configuration
@code
"Problem": {
    "classname" : "Class",
    "kind" : "min",
    "dimension_of_decision_space" : 30,
    "lower_bound_of_decision_space" : -100,
    "upper_bound_of_decision_space" : 100,
    "dimension_of_objective_space" : 1,
    "optimal_solution" : 0
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

    virtual void init(std::shared_ptr<Repository> repos) override;

/**
@brief Evaluate the individual.
@param individual The individual to be evaluated.

Evaluate the individual and increase the Problem::number_of_fitness_evaluations.
@sa evaluation_function()
*/
    void evaluate(std::shared_ptr<Individual> individual) const;

/**
@brief Evaluate the individual by the given function.
@param individual The individual to be evaluated.
*/
    virtual void evaluation_function(std::shared_ptr<Individual> individual) const = 0;

/**
@brief Return the name of the problem.
*/
    const std::string& name() const { return name_; }
/**
@brief Return the kinds of the problem.
*/
    ProblemKind problem_type() const { return problem_kind_; }

/**
@name decision space access
*/
///@{
/**
@brief Return the dimension of decision space.
*/
    unsigned int dimension_of_decision_space() const
    {
        return dimension_of_decision_space_;
    }
/**
@brief Return the lower bound of decision space with specific dimension.
@param dimension The specific dimension of decision space.
*/
    Object lower_bound_of_decision_space(std::size_t dimension) const;
/**
@brief Return the upper bound of decision space with specific dimension.
@param dimension The specific dimension of decision space.
*/
    Object upper_bound_of_decision_space(std::size_t dimension) const;
///@}
/**
@name objective space access
*/
///@{
/**
@brief Return the dimension of objective space.
*/
    unsigned int dimension_of_objective_space() const
    {
        return dimension_of_objective_space_;
    }
/**
@brief Return the lower bound of objective space with specific dimension.
@param dimension The specific dimension of objective space.
*/
    Object lower_bound_of_objective_space(std::size_t dimension) const;
/**
@brief Return the upper bound of objective space with specific dimension.
@param dimension The specific dimension of objective space.
*/
    Object upper_bound_of_objective_space(std::size_t dimension) const;
/**
@brief Return the optimal value of the objective space.
*/
    Object optimal_solution() const { return optimal_solution_; }
///@}

protected:

/// Boundary encapsulates the lower bound and upper bound.
    struct Boundary
    {
        Boundary() = default;
        Boundary(Object lb, Object ub) : lower_bound_(lb), upper_bound_(ub) {}
        Boundary(const Boundary& rhs) = default;
        Object lower_bound_;  ///< The lower bound
        Object upper_bound_;  ///< The upper bound
    };

protected:

/// The name of the problem.
    std::string name_;
/// The kinds of the problem.
    ProblemKind problem_kind_;
/// The dimension of decision space.
    unsigned int dimension_of_decision_space_;
/// The boundaries of the decision space in each dimension.
    std::vector<Boundary> boundaries_of_decision_space_;
/// The dimension of objective space.
    unsigned int dimension_of_objective_space_;
/// The boundaries of the objective space in each dimension.
    std::vector<Boundary> boundaries_of_objective_space_;
/// The optimal solution of the objective space if it exists.
    Object optimal_solution_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override = 0;
};

}

#endif
