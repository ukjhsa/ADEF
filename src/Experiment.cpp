#include <string>
#include <sstream>
#include "Experiment.h"
#include "Random.h"
#include "ExperimentalStatistics.h"
#include "Repository.h"
#include "Problem.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Evolution.h"

namespace adef {

Experiment::Experiment() : name_("experiment"), number_of_runs_(0)
{
}

Experiment::Experiment(const Experiment& rhs) :
    name_(rhs.name_), number_of_runs_(rhs.number_of_runs_)
{
    if (rhs.random_) { random_ = rhs.random_->clone(); }
    if (rhs.statistics_) { statistics_ = rhs.statistics_->clone(); }
    if (rhs.repository_) { repository_ = rhs.repository_->clone(); }
}

void Experiment::setup(const Configuration& config, const PrototypeManager& pm)
{
    number_of_runs_ = config.get_uint_value("number_of_runs");
    random_ = make_and_setup_type<Random>("Random", config, pm);
    statistics_ = make_and_setup_type<ExperimentalStatistics>(
                                "ExperimentalStatistics", config, pm);
    repository_ = make_and_setup_type<Repository>("Repository", config, pm);

    name_ = repository_->algorithm_name() + "_" +
            repository_->problem()->name();
}

void Experiment::run()
{
    for (decltype(number_of_runs_) times = 0; times < number_of_runs_; ++times) {
        // clone a Repository for each run
        auto repos = repository_->clone();
        // initialize all evolutionary states
        repos->init(random_->clone());

        // evolve the evolution
        repos->evolution()->evolve(repos);

        std::stringstream ss;
        ss << name_ << "_run" << times+1;
        statistics_->output_statistics_on_run(repos, ss.str());

        statistics_->take_statistics(repos);
    }
    statistics_->output_statistics(name_ + ".csv");
}

}
