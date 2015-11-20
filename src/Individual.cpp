#include <memory>
#include <vector>
#include <ostream>
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include "Individual.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Problem.h"

namespace adef {

void Individual::setup(const Configuration& config, const PrototypeManager& pm)
{
    fitness_ = 0.0;
}

void Individual::init(std::shared_ptr<Repository> repos)
{
    unsigned int var_size = repos->problem()->dimension_of_decision_space();
    variables_.resize(var_size);

    unsigned int obj_size = repos->problem()->dimension_of_objective_space();
    objectives_.resize(obj_size);
}

std::shared_ptr<Individual> Individual::empty_clone() const
{
    Individual indi;
    indi.variables_.resize(variables_.size());
    indi.objectives_.resize(objectives_.size());
    indi.fitness_ = 0.0;
    return std::make_shared<Individual>(indi);
}

bool Individual::is_valid(std::shared_ptr<const Problem> problem) const
{
    auto dim_decision_space = problem->dimension_of_decision_space();
    for (decltype(dim_decision_space) dim = 0; dim < dim_decision_space; ++dim) {
        if (is_valid(dim, problem) == false) {
            return false;
        }
    }
    return true;
}

bool Individual::is_valid(std::size_t dimension,
                          std::shared_ptr<const Problem> problem) const
{
    auto lower_bound = problem->lower_bound_of_decision_space(dimension);
    auto upper_bound = problem->upper_bound_of_decision_space(dimension);
    auto value = variables(dimension);
    if (std::islessequal(lower_bound, value) &&
        std::islessequal(value, upper_bound)) {
        return true;
    }
    else {
        return false;
    }
}

void Individual::replace(std::shared_ptr<const Individual> rhs)
{
    variables_ = rhs->variables_;
    objectives_ = rhs->objectives_;
    fitness_ = rhs->fitness_;
}

typename Individual::VariableType& Individual::variables(std::size_t index)
{
    return variables_.at(index);
}

const typename Individual::VariableType& Individual::variables(std::size_t index) const
{
    return variables_.at(index);
}

typename Individual::ObjectiveType& Individual::objectives(std::size_t index)
{
    return objectives_.at(index);
}
const typename Individual::ObjectiveType& Individual::objectives(std::size_t index) const
{
    return objectives_.at(index);
}


Individual& Individual::operator=(const Individual& rhs)
{
    Individual temp(rhs);
    std::swap(variables_, temp.variables_);
    std::swap(objectives_, temp.objectives_);
    std::swap(fitness_, temp.fitness_);
    return *this;
}

Individual& Individual::operator+=(const Individual& rhs)
{
    std::size_t size = this->dimension_of_variable(),
                rhs_size = rhs.dimension_of_variable();
    if (size != rhs_size) {
        throw std::logic_error("The size of two Individual are not equal");
    }
    for (std::size_t idx = 0; idx < size; idx++) {
        variables_[idx] += rhs.variables_[idx];
    }
    return *this;
}

Individual& Individual::operator-=(const Individual& rhs)
{
    std::size_t size = this->dimension_of_variable(),
                rhs_size = rhs.dimension_of_variable();
    if (size != rhs_size) {
        throw std::logic_error("The size of two Individual are not equal");
    }
    for (std::size_t idx = 0; idx < size; idx++) {
        variables_[idx] -= rhs.variables_[idx];
    }
    return *this;
}

void Individual::print(std::ostream& os) const
{
    for (auto gene : variables_) {
        os << gene << " ";
    }
    os << std::endl;
}

Individual operator+(const Individual& lhs, const Individual& rhs)
{
    Individual temp(lhs);
    return temp += rhs;
}

Individual operator-(const Individual& lhs, const Individual& rhs)
{
    Individual temp(lhs);
    return temp -= rhs;
}

Individual operator*(const Individual& lhs, double value)
{
    Individual ind(lhs);
    for (unsigned int idx = 0; idx < ind.dimension_of_variable(); ++idx) {
        ind.variables(idx) *= value;
    }
    return ind;
}

Individual operator*(double value, const Individual& rhs)
{
    return rhs * value;
}

}
