#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <ostream>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "SystemStatistics.h"
#include "Experiment.h"
#include "Repository.h"
#include "ExperimentalStatistics.h"
#include "Problem.h"

namespace adef {

void SystemStatistics::setup(const Configuration& config,
                             const PrototypeManager& pm)
{
}

void SystemStatistics::take_statistics(
                                std::shared_ptr<const Experiment> experiment)
{
    auto key = experiment->repository()->problem()->name();
    auto value_key = experiment->repository()->algorithm_name();

    map_fes_[key][value_key] =
        calculate_statistics_items(experiment->statistics()->fes());
    map_error_[key][value_key] =
        calculate_statistics_items(experiment->statistics()->error());
    map_best_fitness_[key][value_key] =
        calculate_statistics_items(experiment->statistics()->best_fitness());

    map_sp_[key][value_key] =
            calculate_statistics_sp(experiment->statistics()->fes(),
                                    experiment->statistics()->error());
}

void SystemStatistics::output_statistics(const std::string& prefix) const
{
    output_statistics_item(prefix + "_FEs.csv",
                           map_fes_);
    output_statistics_item(prefix + "_Error.csv",
                           map_error_);
    output_statistics_item(prefix + "_Fitness_so_far.csv",
                           map_best_fitness_);

    output_success_performance(prefix + "_success_performance.csv");
}

SystemStatistics::Item SystemStatistics::calculate_statistics_items(
                                const std::vector<double>& data) const
{
    Item item;
    item.best_ = data.front();
    item.worst_ = data.front();
    item.mean_ = 0.0;
    for (auto&& run : data) {
        if (run < item.best_) { item.best_ = run; }
        if (item.worst_ < run) { item.worst_ = run; }
        item.mean_ += run;
    }
    item.mean_ /= data.size();

    item.stddev_ = 0.0;
    for (auto&& run : data) {
        item.stddev_ += (run - item.mean_) *
                       (run - item.mean_);
    }
    item.stddev_ /= data.size();
    item.stddev_ = std::sqrt(item.stddev_);

    return item;
}

SystemStatistics::SuccessPerformance SystemStatistics::calculate_statistics_sp(
                                        const std::vector<double>& FEs,
                                        const std::vector<double>& Error) const
{
    auto total_runs = FEs.size();
    if (total_runs != Error.size()) {
        throw std::runtime_error("SystemStatistics accepts different \
                                 total runs of data");
    }

    SuccessPerformance sp;
    sp.NFE_ = 0.0; sp.successful_run_ = 0; sp.successful_rate_ = 0.0;
    for (decltype(total_runs) times = 0; times < total_runs; ++times) {

        auto error = Error[times];
        if (std::abs(error - 0.0) <
            std::numeric_limits<decltype(error)>::epsilon()) {

            sp.NFE_ += FEs[times];
            sp.successful_run_ += 1;
        }
    }
    sp.NFE_ /= total_runs;
    sp.successful_rate_ = static_cast<double>(sp.successful_run_) / total_runs;

    return sp;
}

void SystemStatistics::output_statistics_item(
                                    const std::string& file_name,
                                    const ProblemAlgorithmItemMap& data) const
{
    std::ofstream ofs(file_name);
    if (ofs.is_open()) {

        // collects all names of algorithm
        std::set<std::string> algorithm_names;
        for (auto&& problem2map : data) {
            for (auto&& algorithm2item : problem2map.second) {
                algorithm_names.insert(algorithm2item.first);
            }
        }

        // collects all names of problem
        std::vector<std::string> problem_names;
        for (auto&& problem2map : data) {
            problem_names.push_back(problem2map.first);
        }

        // output
        // The horizontal axis is the name of algorithm
        ofs << "Problem/Algorithm" << ",";
        for (auto&& algorithm : algorithm_names) {
            ofs << algorithm << ",";
        }
        ofs << std::endl;
        // The vertical axis is the name of problem
        for (auto&& p : problem_names) {
            ofs << p << ",";
            if (data.find(p) != data.end()) {
                for (auto&& a : algorithm_names) {
                    if (data.at(p).find(a) != data.at(p).end()) {
                        ofs << "\"" << data.at(p).at(a).best_ << std::endl <<
                                      data.at(p).at(a).worst_ << std::endl <<
                                      data.at(p).at(a).mean_ << std::endl <<
                                      data.at(p).at(a).stddev_ << "\"" << ",";
                    }
                    else {
                        ofs << ",";
                    }
                }
            }
            ofs << std::endl;
        }
    }
}

void SystemStatistics::output_success_performance(
                                        const std::string& file_name) const
{
    std::ofstream ofs(file_name);
    if (ofs.is_open()) {

        // collects all names of algorithm
        std::set<std::string> algorithm_names;
        for (auto&& problem2map : map_sp_) {
            for (auto&& algorithm2item : problem2map.second) {
                algorithm_names.insert(algorithm2item.first);
            }
        }

        // collects all names of problem
        std::vector<std::string> problem_names;
        for (auto&& problem2map : map_sp_) {
            problem_names.push_back(problem2map.first);
        }

        // output
        // The horizontal axis is the name of algorithm
        ofs << "Problem/Algorithm" << ",";
        for (auto&& algorithm : algorithm_names) {
            ofs << algorithm << ",,,,";
        }
        ofs << std::endl;
        for (std::size_t cter = 0; cter < algorithm_names.size(); ++cter) {
            ofs << ",NFE,SRun,SRate,SP";
        }
        ofs << std::endl;
        // The vertical axis is the name of problem
        for (auto&& p : problem_names) {
            ofs << p << ",";

            if (map_sp_.find(p) != map_sp_.end()) {
                for (auto&& a : algorithm_names) {
                    if (map_sp_.at(p).find(a) != map_sp_.at(p).end()) {

                        auto&& sp = map_sp_.at(p).at(a);

                        if (sp.successful_run_ > 0) {
                            ofs << sp.NFE_;
                        }
                        ofs << ",";
                        ofs << sp.successful_run_ << ","
                            << sp.successful_rate_ << ",";
                        if (sp.successful_run_ > 0) {
                            ofs << sp.NFE_ / sp.successful_rate_;
                        }
                        ofs << ",";
                    }
                    else {
                        ofs << ",,,,";
                    }
                }
            }
            ofs << std::endl;
        }
    }
}

}
