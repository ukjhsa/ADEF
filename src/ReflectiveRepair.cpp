#include <memory>
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include "ReflectiveRepair.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Individual.h"
#include "Problem.h"

namespace adef {

void ReflectiveRepair::setup(const Configuration& config,
                             const PrototypeManager& pm)
{
}

void ReflectiveRepair::init(std::shared_ptr<Repository> repos)
{
}

void ReflectiveRepair::repair_function(
                                std::shared_ptr<Individual> individual,
                                std::size_t dim,
                                std::shared_ptr<const Problem> problem) const
{
    auto gene = individual->variables(dim);

    auto nearest_bound = Repair::find_nearest_bound(gene, problem, dim);

    auto diff = std::abs(gene - nearest_bound);
    if (gene < nearest_bound) {
        individual->variables(dim) = nearest_bound + diff;
    }
    else if (gene > nearest_bound){
        individual->variables(dim) = nearest_bound - diff;
    }
    else {
        throw std::logic_error("repair_function error");
    }

    // if it is still not valid
    if (!individual->is_valid(dim, problem)) {
        gene = individual->variables(dim);
        nearest_bound = Repair::find_nearest_bound(gene, problem, dim);
        individual->variables(dim) = nearest_bound;
    }
}

}
