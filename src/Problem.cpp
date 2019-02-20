#include <memory>
#include <string>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Individual.h"
#include "Random.h"

namespace adef {

Problem::Problem(const std::string& name) :
    name_(name), problem_kind_(MIN),
    dimension_of_decision_space_(0), boundaries_of_decision_space_(),
    dimension_of_objective_space_(0), boundaries_of_objective_space_(),
    optimal_solution_(0.0)
{
}

void Problem::setup(const Configuration& config, const PrototypeManager& pm)
{
    auto kind_config = config.get_config("kind");
    if (! kind_config.is_null()) {
        auto kind = kind_config.get_string_value();
        if (kind == "min") { problem_kind_ = MIN; }
        else if (kind == "max") { problem_kind_ = MAX; }
        else { throw std::domain_error("The problem type error."); }
    }

    auto dim_ds_config = config.get_config("dimension_of_decision_space");
    dimension_of_decision_space_ = dim_ds_config.is_null() ?
                                        0 : dim_ds_config.get_uint_value();

    auto lb_ds_config = config.get_config("lower_bound_of_decision_space");
    auto lb_ds = lb_ds_config.is_null() ?
                        0 : lb_ds_config.get_value<Object>();

    auto ub_ds_config = config.get_config("upper_bound_of_decision_space");
    auto ub_ds = ub_ds_config.is_null() ?
                        0 : ub_ds_config.get_value<Object>();
    boundaries_of_decision_space_.resize(dimension_of_decision_space_,
                                         Boundary(lb_ds, ub_ds));

    auto dim_os_config = config.get_config("dimension_of_objective_space");
    dimension_of_objective_space_ = dim_os_config.is_null() ?
                                            0 : dim_os_config.get_uint_value();

    auto lb_os_config = config.get_config("lower_bound_of_objective_space");
    auto lb_os = lb_os_config.is_null() ?
                        0 : lb_os_config.get_value<Object>();

    auto ub_os_config = config.get_config("upper_bound_of_objective_space");
    auto ub_os = ub_os_config.is_null() ?
                        0 : ub_os_config.get_value<Object>();
    boundaries_of_objective_space_.resize(dimension_of_objective_space_,
                                          Boundary(lb_os, ub_os));

    auto optimal_config = config.get_config("optimal_solution");
    optimal_solution_ = optimal_config.is_null() ?
                            0 : optimal_config.get_value<Object>();
}

void Problem::init(std::shared_ptr<Repository> repos)
{
    random_ = repos->random();
}

void Problem::evaluate(std::shared_ptr<Individual> individual) const
{
    evaluation_function(individual);
}

Problem::Object Problem::lower_bound_of_decision_space(std::size_t dimension) const
{
    return boundaries_of_decision_space_.at(dimension).lower_bound_;
}

Problem::Object Problem::upper_bound_of_decision_space(std::size_t dimension) const
{
    return boundaries_of_decision_space_.at(dimension).upper_bound_;
}

Problem::Object Problem::lower_bound_of_objective_space(std::size_t dimension) const
{
    return boundaries_of_objective_space_.at(dimension).lower_bound_;
}

Problem::Object Problem::upper_bound_of_objective_space(std::size_t dimension) const
{
    return boundaries_of_objective_space_.at(dimension).upper_bound_;
}

}
