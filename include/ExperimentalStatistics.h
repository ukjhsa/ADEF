#ifndef EXPERIMENTAL_STATISTICS_H
#define EXPERIMENTAL_STATISTICS_H

#include <memory>
#include <vector>
#include <string>
#include "Prototype.h"

namespace adef {

class Repository;

/**
@brief ExperimentalStatistics handles the statistics of a experiment.

ExperimentalStatistics collects the data of each run, including
1. the number of the fitness evaluations (FEs)
2. the error
3. the best fitness
.
*/
class ExperimentalStatistics : public Prototype
{
public:

/// The type of the list of @em T on each run.
    template<typename T>
    using RunList = std::vector<T>;

    virtual ~ExperimentalStatistics() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<ExperimentalStatistics> clone() const
    {
        return std::dynamic_pointer_cast<ExperimentalStatistics>(clone_impl());
    }
/**
@brief Set up the internal states.

ExperimentalStatistics has the following configuration:
- JSON configuration
@code
"ExperimentalStatistics" : {
    "classname" : "ExperimentalStatistics"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

/**
@brief Take the statistics.
*/
    virtual void take_statistics(std::shared_ptr<const Repository> repos);
/**
@brief Output the statistics on the run level.
@param repos The Repository to output the statistics.
@param prefix The prefix of the file name.
*/
    virtual void output_statistics_on_run(
                                    std::shared_ptr<const Repository> repos,
                                    const std::string& prefix) const;
/**
@brief Output the statistics.
@param file_name The file name.
*/
    virtual void output_statistics(const std::string& file_name);
/**
@brief Return the number of the fitness evaluations on each run.
*/
    const RunList<double>& fes() const { return fes_; }
/**
@brief Return the error on each run.
*/
    const RunList<double>& error() const { return error_; }
/**
@brief Return the value of the best fitness on each run.
*/
    const RunList<double>& best_fitness() const { return best_fitness_; }

protected:

/// The number of the fitness evaluations of each run.
    RunList<double> fes_;
/// The error of each run.
    RunList<double> error_;
/// The best fitness of each run.
    RunList<double> best_fitness_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<ExperimentalStatistics>(*this);
    }
};

}

#endif // EXPERIMENTAL_STATISTICS_H
