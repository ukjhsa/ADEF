#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include "ExperimentalStatistics.h"
#include "Repository.h"
#include "Statistics.h"

namespace adef {

void ExperimentalStatistics::setup(const Configuration& config,
                                   const PrototypeManager& pm)
{
}

void ExperimentalStatistics::take_statistics(
                                        std::shared_ptr<const Repository> repos)
{
    fes_.push_back(repos->statistics()->number_of_fitness_evaluations());
    error_.push_back(repos->statistics()->evolve_error(repos));
    best_fitness_.push_back(repos->statistics()->best_fitness_so_far());
}

void ExperimentalStatistics::output_statistics_on_run(
                                        std::shared_ptr<const Repository> repos,
                                        const std::string& prefix) const
{
    repos->statistics()->output_statistics(prefix);
}

void ExperimentalStatistics::output_statistics(const std::string& file_name)
{
    std::ofstream ofs(file_name);
    ofs << "FEs,Error,best_fitness" << std::endl;

    auto it_fes = std::begin(fes_);
    auto it_error = std::begin(error_);
    auto it_best_fitness = std::begin(best_fitness_);
    for (;
         it_fes != std::end(fes_) && it_error != std::end(error_) &&
            it_best_fitness != std::end(best_fitness_);
         ++it_fes, ++it_error, ++it_best_fitness) {

        ofs << *it_fes << "," <<
               *it_error << "," <<
               *it_best_fitness << std::endl;
    }
}

}
