#ifndef DE_REPRODUCTION_H
#define DE_REPRODUCTION_H

#include <memory>
#include "Reproduction.h"

namespace adef {

class Configuration;
class PrototypeManager;
class Repository;

/**
@brief DEReproduction reproduces offspring according to the DE algorithm.

@par The configuration
DEReproduction has no extra configurations.@n
See setup() for the details.
*/
class DEReproduction : public Reproduction
{
public:

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<DEReproduction> clone() const
    {
        return std::dynamic_pointer_cast<DEReproduction>(clone_impl());
    }
/**
@brief Set up the internal states.

DEReproduction's configuration should be
- JSON configuration
@code
"Reproduction": {
    "classname" : "DEReproduction"
}
@endcode
.
*/
    void setup(const Configuration& config,
               const PrototypeManager& pm) override;

    void init(std::shared_ptr<Repository> repos) override;

    void reproduce(std::shared_ptr<Repository> repos) const override;

private:

    std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<DEReproduction>(*this);
    }
};

}

#endif
