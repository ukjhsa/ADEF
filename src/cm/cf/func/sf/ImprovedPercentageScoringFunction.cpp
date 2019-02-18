#include <memory>
#include "cm/cf/func/sf/ImprovedPercentageScoringFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

void ImprovedPercentageScoringFunction::setup(const Configuration & config, const PrototypeManager & pm)
{
}

ImprovedPercentageScoringFunction::Score ImprovedPercentageScoringFunction::calculate_score(std::shared_ptr<const Individual> parent, std::shared_ptr<const Individual> offspring) const
{
    return parent->fitness() - offspring->fitness();
}

}
