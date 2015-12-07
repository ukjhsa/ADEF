#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <string>
#include <vector>
#include "Prototype.h"

namespace adef {

class SystemStatistics;
class Experiment;
class Configuration;
class PrototypeManager;

/**
@brief System is the top class to clients.

System contains one or many experiments and generates the analysis of
all experiments.

Call System::run() to execute.

@par The configuration
System has extra configurations:
- member
    - name: "name"
    - value: @c string
- member
    - name: "SystemStatistics"
    - value: object configuration which represents SystemStatistics.
- member
    - name: "Experiment"
    - value: array configuration
        - elements: object configuration which represents Experiment.
.
See setup() for the details.

@sa see Experiment and Repository for the contents.
*/
class System : public Prototype
{
public:

    System();
    System(const System& rhs);
    virtual ~System() = default;
    System& operator=(const System& rhs) = delete;

/**
@brief Clone the current class.
@sa clone_impl()
*/
    std::shared_ptr<System> clone() const
    {
        return std::dynamic_pointer_cast<System>(clone_impl());
    }
/**
@brief Set up the internal states.

If System has the following configuration:
- name: Name
.
its configuration should be
- JSON configuration
@code
"System" : {
    "classname" : "System",
    "name" : "Name",
    "SystemStatistics" : {
        ...skip...
    },
    "Experiment" : [
        ...skip...
    ]
}
@endcode
.
*/
    virtual void setup(const Configuration& config,
                       const PrototypeManager& pm) override;
/**
@brief Execute experiments.

It calls Experiment::run() to execute each experiment. After finishing
all of experiments, it outputs the statistics of entire experiments.
*/
    virtual void run();

protected:

/**
@brief The prefix of the file name of output data.
*/
    std::string name_;
/**
@brief The statistics on the system level.
*/
    std::shared_ptr<SystemStatistics> statistics_;
/**
@brief The total experiments.
*/
    std::vector<std::shared_ptr<Experiment>> experiments_;

private:

    virtual std::shared_ptr<Prototype> clone_impl() const override
    {
        return std::make_shared<System>(*this);
    }
};

}

#endif // SYSTEM_H
