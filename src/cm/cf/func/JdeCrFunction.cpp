#include <memory>
#include <vector>
#include <string>
#include <random>
#include "cm/cf/func/JdeCrFunction.h"
#include "Any.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Random.h"
#include "Individual.h"

namespace adef {

void JdeCrFunction::setup(const Configuration & config, const PrototypeManager & pm)
{
    auto object_config = config.get_config("object");
    auto object = make_and_setup_type<BaseFunction>(object_config, pm);
    object->set_function_name("object");
    add_function(object);

    auto tau_config = config.get_config("tau");
    auto tau = make_and_setup_type<BaseFunction>(tau_config, pm);
    tau->set_function_name("tau");
    add_function(tau);

    object_ = 0.9;
    tau_ = 0.1;
}

JdeCrFunction::Object JdeCrFunction::generate()
{
    std::mt19937 gen(random_->random());
    std::uniform_real_distribution<> uniform;
    if (uniform(gen) < tau_) {
        return uniform(gen);
    }
    else {
        return object_;
    }
}

void JdeCrFunction::update()
{
    auto object = get_function("object");
    object->update();
    object_ = object->generate();

    auto tau = get_function("tau");
    tau->update();
    tau_ = tau->generate();
}

unsigned int JdeCrFunction::number_of_parameters() const
{
    return 0;
}

}

