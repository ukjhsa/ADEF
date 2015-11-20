#include <memory>
#include <stdexcept>
#include <string>
#include "Repair.h"
#include "Repository.h"
#include "Population.h"
#include "Individual.h"
#include "Problem.h"

namespace adef {

void Repair::repair(std::shared_ptr<Repository> repos) const
{
    auto pop = repos->offspring();
    auto pop_size = pop->population_size();
    for (decltype(pop_size) idx = 0; idx < pop_size; ++idx) {
        repair(pop->at(idx), repos->problem());
    }
}

void Repair::repair(std::shared_ptr<Individual> individual,
                    std::shared_ptr<const Problem> problem) const
{
    auto dim_decision_space = problem->dimension_of_decision_space();
    for (decltype(dim_decision_space) dim = 0; dim < dim_decision_space; ++dim) {
        if (!individual->is_valid(dim, problem)) {
            repair_function(individual, dim, problem);
        }
    }
}

double Repair::find_nearest_bound(double gene,
                                  std::shared_ptr<const Problem> problem,
                                  std::size_t dim) const
{
    auto lower_bound = problem->lower_bound_of_decision_space(dim);
    auto upper_bound = problem->upper_bound_of_decision_space(dim);

    if (gene < lower_bound) {
        return lower_bound;
    }
    else if (gene > upper_bound){
        return upper_bound;
    }
    else {
        throw std::logic_error("find_nearest_bound error");
    }
}

}
