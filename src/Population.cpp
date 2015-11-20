#include <memory>
#include <vector>
#include <cstddef>
#include <functional>
#include <ostream>
#include <algorithm>
#include "Population.h"
#include "Configuration.h"
#include "PrototypeManager.h"
#include "Repository.h"
#include "Individual.h"

namespace adef {

Population::Population(const Population& rhs)
{
    individuals_.resize(rhs.population_size());
    for (std::size_t dim = 0; dim < rhs.population_size(); ++dim) {

            individuals_[dim] = rhs.individuals_[dim]->clone();
    }
}

void Population::setup(const Configuration& config, const PrototypeManager& pm)
{
    unsigned int pop_size = config.get_uint_value("population_size");
    individuals_.resize(pop_size);

    auto individual = make_and_setup_type<Individual>("Individual", config, pm);
    for (auto& indi : individuals_) {
        indi = individual->clone();
    }
}

void Population::init(std::shared_ptr<Repository> repos)
{
    for (auto& indi : individuals_) {
        indi->init(repos);
    }
}

std::shared_ptr<Population> Population::empty_clone() const
{
    Population pop;
    pop.individuals_.resize(population_size());
    for (std::size_t idx = 0; idx < population_size(); ++idx) {
        pop.individuals_[idx] = individuals_[idx]->empty_clone();
    }
    return std::make_shared<Population>(pop);
}

void Population::apply_to_each_individual(
            std::function<void(std::shared_ptr<Individual>)> func)
{
    std::for_each(individuals_.begin(), individuals_.end(), func);
}

void Population::replace(std::shared_ptr<const Population> rhs)
{
    auto pop_size = individuals_.size();
    auto rhs_pop_size = rhs->individuals_.size();

    if (pop_size != rhs_pop_size) { individuals_.resize(rhs_pop_size); }

    for (decltype(rhs_pop_size) idx = 0; idx < rhs_pop_size; ++idx) {

        individuals_[idx]->replace(rhs->individuals_[idx]);
    }
}

std::shared_ptr<Individual> Population::at(std::size_t index)
{
    return individuals_.at(index);
}

std::shared_ptr<const Individual> Population::at(std::size_t index) const
{
    return individuals_.at(index);
}

std::shared_ptr<Individual> Population::operator[](std::size_t index)
{
    return individuals_[index];
}

std::shared_ptr<const Individual> Population::operator[](std::size_t index) const
{
    return individuals_[index];
}

void Population::print(std::ostream& os) const
{
    for (auto ind : individuals_) {
        ind->print(os);
    }
    os << std::endl;
}

}
