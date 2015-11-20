#ifndef EVOLUTIONARY_STATE_H
#define EVOLUTIONARY_STATE_H

#include <memory>

namespace adef {

class Repository;

/**
@brief EvolutionaryState is the abstract base class of
participating the process of evolution.

EvolutionaryState defines the interface init() which is used in the
initialization of the process of evolution.

@sa Repository for which contains evolutionary states.
*/
class EvolutionaryState
{
public:

    virtual ~EvolutionaryState() = default;

/**
@brief Initialize this state from other states.
@param repos The Repository to get initialization informations.
*/
    virtual void init(std::shared_ptr<Repository> repos) = 0;
};

}

#endif // EVOLUTIONARY_STATE_H
