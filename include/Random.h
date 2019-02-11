#ifndef RANDOM_H
#define RANDOM_H

#include <memory>
#include "Prototype.h"

namespace adef {

/**
@brief Random generate pseudo-random number.

@par The configuration
Random has extra configurations:
- member
    - name: "seed"
    - value: <tt>unsigned int</tt>
.
See setup() for the details.
*/
class Random : public Prototype
{
public:

    Random();
    Random(const Random& rhs);
    virtual ~Random() = default;
    Random& operator=(const Random& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<Random> clone() const
    {
        return std::dynamic_pointer_cast<Random>(clone_impl());
    }
/**
@brief Set up the internal states.

Random has the following configuration:
- JSON configuration
@code
"Random" : {
    "classname" : "Random",
    "seed" : 0
}
@endcode
.
*/
    virtual void setup(const Configuration& config, const PrototypeManager& pm) override;

    unsigned int seed() const { return seed_; }

    int random() const;

protected:
    unsigned int seed_;

private:
    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<Random>(*this);
    }
};

} // namespace adef

#endif // RANDOM_H
