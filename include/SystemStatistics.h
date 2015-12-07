#ifndef SYSTEM_STATISTICS_H
#define SYSTEM_STATISTICS_H

#include <memory>
#include <map>
#include <string>
#include <vector>
#include "Prototype.h"

namespace adef {

class Experiment;

/**
@brief SystemStatistics handles the statistics of entire system.

SystemStatistics collects the data of each experiment, including
1. the number of the fitness evaluations (FEs)
2. the error
3. the best fitness
.
then calculates the value of above data:
1. the best value
2. the worst value
3. the mean value
4. the standard deviation
5. the success performance
.
by formula
- success performance = (the mean of FEs for successful runs) *
(the number of the total runs) / (the number of the successful runs)
.
*/
class SystemStatistics : public Prototype
{
public:

    virtual ~SystemStatistics() = default;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<SystemStatistics> clone() const
    {
        return std::dynamic_pointer_cast<SystemStatistics>(clone_impl());
    }
/**
@brief Set up the internal states.

SystemStatistics has the following configuration:
- JSON configuration
@code
"SystemStatistics" : {
    "classname" : "SystemStatistics"
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;
/**
@brief Take the statistics.
@param experiment The Experiment to take the statistics.
*/
    virtual void take_statistics(std::shared_ptr<const Experiment> experiment);
/**
@brief Output the statistics.
@param prefix The prefix of the file name.
*/
    virtual void output_statistics(const std::string& prefix) const;

protected:

/// Item contains the statistical items.
    struct Item {
        double best_;    ///< The best value.
        double worst_;   ///< The worst value.
        double mean_;    ///< The mean value.
        double stddev_;  ///< The standard deviation.
    };
/// The type of the map of the name of algorithm to statistical item
    using AlgorithmItemMap =
                        std::map<std::string, Item>;
/// The type of the map of the name of problem to AlgorithmItemMap
    using ProblemAlgorithmItemMap =
                        std::map<std::string, AlgorithmItemMap>;

/// The statistics of the number of the fitness evaluations.
    ProblemAlgorithmItemMap map_fes_;
/// The statistics of the error.
    ProblemAlgorithmItemMap map_error_;
/// The statistics of the best fitness.
    ProblemAlgorithmItemMap map_best_fitness_;
/**
@brief Calculate the statistical items.
*/
    Item calculate_statistics_items(const std::vector<double>& data) const;
/**
@brief Output the statistical item.
*/
    void output_statistics_item(const std::string& file_name,
                                const ProblemAlgorithmItemMap& data) const;

protected:

/// SuccessPerformance contains informations of the success performance.
    struct SuccessPerformance {
/// The mean of the number of the fitness evaluations.
        double NFE_;
/// The number of the successful runs.
        unsigned int successful_run_;
/// The successful rate.
        double successful_rate_;
    };

/// The type of the map of the name of algorithm to the success performance
    using AlgorithmSPMap =
                        std::map<std::string, SuccessPerformance>;
/// The type of the map of the name of algorithm to AlgorithmSPMap
    using ProblemAlgorithmSPMap =
                        std::map<std::string, AlgorithmSPMap>;

/// The statistics of the success performance.
    ProblemAlgorithmSPMap map_sp_;
/**
@brief Calculate the statistics of success performance.
*/
    SuccessPerformance calculate_statistics_sp(
                                        const std::vector<double>& FEs,
                                        const std::vector<double>& Error) const;
/**
@brief Output the statistics of success performance.
*/
    void output_success_performance(const std::string& file_name) const;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<SystemStatistics>(*this);
    }
};

}

#endif // SYSTEM_STATISTICS_H
