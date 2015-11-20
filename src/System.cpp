#include <memory>
#include <string>
#include <vector>
#include "System.h"
#include "SystemStatistics.h"
#include "Experiment.h"
#include "Configuration.h"
#include "PrototypeManager.h"

namespace adef {

System::System() : name_("system")
{
}

System::System(const System& rhs) :
    name_(rhs.name_)
{
    if (rhs.statistics_) { statistics_ = rhs.statistics_->clone(); }

    experiments_.resize(rhs.experiments_.size());
    for (std::size_t idx = 0; idx < rhs.experiments_.size(); ++idx) {

                experiments_[idx] = rhs.experiments_[idx]->clone();
    }
}

void System::setup(const Configuration& config, const PrototypeManager& pm)
{
    name_ = config.get_string_value("name");
    statistics_ = make_and_setup_type<SystemStatistics>("SystemStatistics",
                                                        config, pm);

    auto exps_config = config.get_config("Experiment");
    auto exp_size = exps_config.get_array_size();
    for (decltype(exp_size) idx = 0; idx < exp_size; ++idx) {
        auto exp_config = exps_config.get_config(idx);
        auto exp = make_and_setup_type<Experiment>(exp_config, pm);
        experiments_.push_back(exp);
    }
}

void System::run()
{
    for (auto&& exp : experiments_) {
        exp->run();

        statistics_->take_statistics(exp);
    }
    statistics_->output_statistics(name_);
}

}
