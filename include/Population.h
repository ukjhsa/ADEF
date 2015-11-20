#ifndef POPULATION_H
#define POPULATION_H

#include <memory>
#include <vector>
#include <cstddef>
#include <functional>
#include <ostream>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;
class Individual;

/**
@brief Population contains total individuals.

The data structure of individuals are invisible to other classes.
The ways to access individuals are
- Access an individual in each time.
- Apply a function to each individual.

@par The configuration
Population has extra configurations:
- member
    - name: "population_size"
    - value: <tt>unsigned int</tt>
- member
    - name: "Individual"
    - value: object configuration which represents Individual.
.
See setup() for the details.
@sa Individual
*/
class Population : public Prototype, public EvolutionaryState
{
public:

    Population() = default;
    Population(const Population& rhs);
    virtual ~Population() = default;
    Population& operator=(const Population& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Population> clone() const
    {
        return std::dynamic_pointer_cast<Population>(clone_impl());
    }
/**
@brief Set up the internal states.

If Population has the following configuration:
- population_size: 50
.
its configuration should be
- JSON configuration
@code
"Population" : {
    "classname" : "Population",
    "population_size" : 50,
    "Individual" : {
        ...skip...
    }
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

    virtual void init(std::shared_ptr<Repository> repos) override;

/**
@brief Clone the current class with default state.
*/
    std::shared_ptr<Population> empty_clone() const;
/**
@brief Replace the contents to other.
*/
    void replace(std::shared_ptr<const Population> rhs);
/**
@name Individual operators
The operators of accessing individuals.
*/
///@{
/**
@brief Apply a function to each individual.
*/
    void apply_to_each_individual(
            std::function<void(std::shared_ptr<Individual>)> func);
/**
@brief Return the population size.
*/
    std::size_t population_size() const { return individuals_.size(); }
/**
@brief Access the individual with bounds checking.
@param index The index of individual.
*/
    std::shared_ptr<Individual> at(std::size_t index);
/**
@brief Access the individual with bounds checking.
@param index The index of individual.
*/
    std::shared_ptr<const Individual> at(std::size_t index) const;
/**
@brief Access the individual.
@param index The index of individual.
*/
    std::shared_ptr<Individual> operator[](std::size_t index);
/**
@brief Access the individual.
@param index The index of individual.
*/
    std::shared_ptr<const Individual> operator[](std::size_t index) const;
///@}

/**
@brief Print total individuals.
@param os The @c std::ostream to print to.
*/
    void print(std::ostream& os) const;

protected:

/// The individuals.
    std::vector<std::shared_ptr<Individual>> individuals_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Population>(*this);
    }
};

}

#endif
