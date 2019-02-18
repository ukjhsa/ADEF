#include <memory>
#include <string>
#include <vector>
#include <any>
#include <stdexcept>
#include "cm/cu/SdeFControlUpdate.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Random.h"
#include "cm/cp/ControlParameter.h"
#include "cm/cf/func/Function.h"
#include "Population.h"

namespace adef {

void SdeFControlUpdate::setup(const Configuration& config, const PrototypeManager& pm)
{
}

void SdeFControlUpdate::update(std::shared_ptr<Repository> repos,
    std::shared_ptr<BaseControlParameter> parameter,
    std::shared_ptr<BaseFunction> function) const
{
    auto param = std::dynamic_pointer_cast<ControlParameter<Object>>(parameter);
    auto func = std::dynamic_pointer_cast<Function<Object>>(function);

    std::vector<std::size_t> temp;
    auto number_param = func->number_of_parameters();
    auto indices = exclusive_random_generator(temp,
        number_param,
        0,
        repos->population()->population_size(),
        repos->random());

    std::vector<std::any> record;
    for (auto& index : indices) {
        record.push_back(param->load(index));
    }
    auto succ = func->record(record);
    if (!succ) {
        throw std::runtime_error(
            "No functions accept parameters "
            "in the \"" + function->function_name() + "\"");
    }
}

std::vector<std::size_t> SdeFControlUpdate::exclusive_random_generator(
    std::vector<std::size_t>& used_numbers,
    unsigned int number_of_result,
    unsigned int min_range,
    unsigned int max_range,
    std::shared_ptr<Random> random) const
{
    std::vector<std::size_t> result(number_of_result);
    for (auto& res : result) {

        std::size_t rnd = random->random() % (max_range - min_range) + min_range;
        for (std::size_t counter = 0; counter < used_numbers.size(); ) {
            for (auto used : used_numbers) {
                if (rnd == used) {
                    counter = 0;
                    break;
                }
                ++counter;
            }
            rnd = random->random() % (max_range - min_range) + min_range;
        }
        res = rnd;
        used_numbers.push_back(rnd);
    }
    return result;
}

}
