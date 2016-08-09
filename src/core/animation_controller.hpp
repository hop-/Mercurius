#ifndef _CORE_ANIMATION_CONTROLLER_HPP_
#define _CORE_ANIMATION_CONTROLLER_HPP_

#include <vector>
#include <string>

namespace Core
{

class AnimationState;

class AnimationController
{
    using States = std::vector<AnimationState*>;
    States m_states;
    unsigned m_currentState;

public:
    /**
     * @brief Adds new state into controller
     * @param state AnimationState
     */
    void addState(AnimationState* state);

    /**
     * @brief Removes state with name from controller
     * @param name stirng state name
     */
    void removeState(const std::string& name);

    /**
     * @brief Changes current state to state with name
     * @param name stirng state name
     */
    void changeState(const std::string& name);

public:
    /**
     * @brief Regular update, updates current state
     */
    void update();

private:
    void removeState(unsigned id);
    void changeState(unsigned id);
    int stateID(const std::string& name) const;
};

} // namespace Core

#endif //_CORE_ANIMATION_CONTROLLER_HPP_
