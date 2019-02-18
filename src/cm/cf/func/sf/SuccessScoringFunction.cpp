#include <memory>
#include "cm/cf/func/sf/SuccessScoringFunction.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Individual.h"

namespace adef {

void SuccessScoringFunction::setup(const Configuration & config, const PrototypeManager & pm)
{
}

SuccessScoringFunction::Score SuccessScoringFunction::calculate_score(std::shared_ptr<const Individual> parent, std::shared_ptr<const Individual> offspring) const
{
    if (offspring->fitness() < parent->fitness()) {
        return 1;
    }
    else {
        return 0;
    }
}

}
