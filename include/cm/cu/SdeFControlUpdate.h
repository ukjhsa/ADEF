#ifndef SDE_F_CONTROL_UPDATE_H
#define SDE_F_CONTROL_UPDATE_H

#include <memory>
#include <string>
#include <stdexcept>
#include "ControlUpdate.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "cm/cp/ControlParameter.h"
#include "cm/cf/func/Function.h"
#include "Population.h"

namespace adef {

/**
@brief SdeFControlUpdate updates internal states by
the procedure of F value in the SDE algorithm.

@par The configuration
SdeFControlUpdate has no extra configurations.@n
See setup() for the details.
*/
class SdeFControlUpdate : public ControlUpdate
{
public:

/// The type of the object
    using Object = double;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<SdeFControlUpdate> clone() const
    {
        return std::dynamic_pointer_cast<SdeFControlUpdate>(clone_impl());
    }
/**
@brief Set up the internal states.

If @em SomeThing is SdeFControlUpdate,@n
its configuration should be
- JSON configuration
@code
"SomeThing": {
    "classname" : "SdeFControlUpdate"
}
@endcode
.
*/
    void setup(const Configuration& config, const PrototypeManager& pm) override
    {
    }

    void update(std::shared_ptr<Repository> repos,
                std::shared_ptr<BaseControlParameter> parameter,
                std::shared_ptr<BaseFunction> function) const override
    {
        auto param = std::dynamic_pointer_cast<ControlParameter<Object>>(parameter);
        auto func = std::dynamic_pointer_cast<Function<Object>>(function);

        std::vector<std::size_t> temp;
        auto number_param = func->number_of_parameters();
        auto indices = exclusive_random_generator(temp,
                                                  number_param,
                                                  0,
                                                  repos->population()->population_size());

        std::vector<Any> record;
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

private:

    std::vector<std::size_t> exclusive_random_generator(
                                       std::vector<std::size_t>& used_numbers,
                                       unsigned int number_of_result,
                                       unsigned int min_range,
                                       unsigned int max_range) const
    {
        std::vector<std::size_t> result(number_of_result);
        for (auto& res : result) {

            std::size_t rnd = rand() % (max_range-min_range) + min_range;
            for (std::size_t counter = 0; counter < used_numbers.size(); ) {
                for (auto used : used_numbers) {
                    if (rnd == used) {
                        counter = 0;
                        break;
                    }
                    ++counter;
                }
                rnd = rand() % (max_range-min_range) + min_range;
            }
            res = rnd;
            used_numbers.push_back(rnd);
        }
        return result;
    }

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<SdeFControlUpdate>(*this);
    }
};

}

#endif // SDE_F_CONTROL_UPDATE_H
