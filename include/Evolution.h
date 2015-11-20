#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <memory>
#include "Prototype.h"
#include "EvolutionaryState.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;

/**
@brief Evolution controls the evolution flow.

Call Evolution::evolve() to evolve.

@par The configuration
Evolution has extra configurations:
- member
    - name: "max_generation"
    - value: <tt>unsigned int</tt>
.
See setup() for the details.
*/
class Evolution : public Prototype, public EvolutionaryState
{
public:

    virtual ~Evolution() = default;
    Evolution& operator=(const Evolution& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Evolution> clone() const
    {
        return std::dynamic_pointer_cast<Evolution>(clone_impl());
    }

/**
@brief Set up the internal states.

If Evolution has the following configuration:
- max_generation: 10000
.
its configuration should be
- JSON configuration
@code
"Evolution" : {
    "classname" : "Evolution",
    "max_generation" : 10000
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;

    virtual void init(std::shared_ptr<Repository> repos) override;

/**
@brief Evolve the algorithm.
@param repos The Repository to evolve.
*/
    virtual void evolve(std::shared_ptr<Repository> repos) const;

protected:

/**
@brief Check the termination of evolution.
@param repos The Repository to check the termination.
@return true if it reached the termination.
*/
    virtual bool is_evolve_terminated(std::shared_ptr<const Repository> repos) const;

protected:

/**
@brief The maximum of the number of generation.
*/
    unsigned int max_generation_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Evolution>(*this);
    }
};

}

#endif
