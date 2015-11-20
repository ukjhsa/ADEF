#ifndef STATISTICS_H
#define STATISTICS_H

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Population;

/**
@brief Statistics handles the statistics of an evolution.

Statistics collects the data of each generation, including
1. the number of the fitness evaluations (FEs)
2. the best fitness
3. the best fitness so far
4. Statistics::Item of all individuals
.
For the statistics of Statistics::Item, it can be configured by the
configuration file to specify which items can be collected and output.

@par The configuration
Statistics has extra configurations:
- member (optional)
    - name: "success_error"
    - value: @c double
.
- member
    - name: "item"
    - value: array configuration
        - elements: one or some or all of "parents", "offspring", "f", "cr"
.
It has default configurations:
- success_error: 0.00001
.
See setup() for the details.
*/
class Statistics : public Prototype, public EvolutionaryState
{
public:

/// The statistical item.
    enum class Item {
        parents,    ///< The fitness values of parents.
        offspring,  ///< The fitness values of offspring.
        cr,         ///< The values of parameter @em CR.
        f           ///< The values of parameter @em F.
    };

/// The type of the list of @em T on each generation.
    template<typename T>
    using GenerationList = std::vector<T>;
/// The type of the list of values of all individuals.
    using AllIndividualsValueList = std::vector<double>;

    Statistics();
    Statistics(const Statistics& rhs) = default;
    virtual ~Statistics() = default;
    Statistics& operator=(const Statistics& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Statistics> clone() const
    {
        return std::dynamic_pointer_cast<Statistics>(clone_impl());
    }

/**
@brief Set up the internal states.

If Statistics has the following configuration:
- item: parents, offspring, f, cr
.
its configuration should be
- JSON configuration
@code
"Statistics" : {
    "classname" : "Statistics",
    "item" : [
        "parents",
        "offspring",
        "f",
        "cr"
    ]
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

    virtual void init(std::shared_ptr<Repository> repos) override;

/**
@brief Take statistics on each generation.
*/
    virtual void take_statistics(std::shared_ptr<const Repository> repos);
/**
@brief Take statistics on post-reproduction.
*/
    virtual void post_reproduction_statistic(std::shared_ptr<const Repository> repos);
/**
@brief Store statistical item of all individuals.
@param item The statistical item to store.
@param values The values of all individuals to store.
*/
    void store_statistics_all_individuals(Item item,
                                        const AllIndividualsValueList& values);
/**
@brief Output the statistics.
@param prefix The prefix of the file name.
*/
    virtual void output_statistics(const std::string& prefix) const;
/**
@brief Check whether the evolution success.
@return True if the evolution success.
*/
    bool is_evolve_success(std::shared_ptr<const Repository> repos) const;
/**
@brief Return the error between the experimental data and the optimal value.
*/
    double evolve_error(std::shared_ptr<const Repository> repos) const;
/**
@brief Return the best fitness of each generation.
*/
    const GenerationList<double>& best_fitness() const
    {
        return best_fitness_;
    }
/**
@brief Return the best fitness so far.
*/
    double best_fitness_so_far() const
    {
        return best_fitness_so_far_;
    }
/**
@brief Increase the number of fitness evaluations.
*/
    void increase_number_of_fitness_evaluations()
    {
        ++number_of_fitness_evaluations_;
    }
/**
@brief Return the number of fitness evaluations.
*/
    unsigned int number_of_fitness_evaluations() const
    {
        return number_of_fitness_evaluations_;
    }

protected:

/**
@brief Output all statistical items.
@param prefix The prefix of the file name.
*/
    void output_all_statistical_items(const std::string& prefix) const;
/**
@brief Output the best fitness
@param prefix The prefix of the file name.
*/
    void output_best_fitness(const std::string& prefix) const;
/**
@brief Output the statistical item.
*/
    void output_statistical_items(const std::string& file_name,
                    const GenerationList<AllIndividualsValueList>& data) const;

/**
@brief Take statistics of population.
@param item The statistical item to store.
@param population The population to take statistics.
*/
    void take_statistics_population(Item item,
                                  std::shared_ptr<const Population> population);
/**
@brief Update the best fitness so far.
@param fitness The current fitness.
*/
    void update_best_fitness_so_far(double fitness);

protected:

/// The success error between solution and optimal solution.
    double success_error_;

/// The map of Item-name pairs.
    std::map<Item, std::string> map_item_to_name_;
/// The names of the statistical items.
    std::vector<std::string> names_of_items_;

/// The statistics of values of all individuals.
    std::map<Item,
             GenerationList<AllIndividualsValueList>
             > statistics_all_individuals_;

/// The best fitness of each generation.
    GenerationList<double> best_fitness_;
/// The best fitness so far.
    double best_fitness_so_far_;
/// The number of the fitness evaluations.
    unsigned int number_of_fitness_evaluations_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Statistics>(*this);
    }
};

}

#endif

