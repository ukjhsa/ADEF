#include <memory>
#include <cstddef>
#include "BoundedRepair.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Individual.h"
#include "Problem.h"

namespace adef {

void BoundedRepair::setup(const Configuration& config,
                          const PrototypeManager& pm)
{
}

void BoundedRepair::init(std::shared_ptr<Repository> repos)
{
}

void BoundedRepair::repair_function(std::shared_ptr<Individual> individual,
                                    std::size_t dim,
                                    std::shared_ptr<const Problem> problem) const
{
    auto gene = individual->variables(dim);

    auto nearest_bound = Repair::find_nearest_bound(gene, problem, dim);

    individual->variables(dim) = nearest_bound;
}

}
