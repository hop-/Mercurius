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
    void removeState(std::string name);

    /**
     * @brief Changes current state to state with name
     * @param name stirng state name
     */
    void changeState(std::string name);

public:
    /**
     * @brief Regular update, updates current state
     */
    void update();

private:
    /**
     * @brief Removes state with ID from controller
     * @param id unsigned int state id in controller
     */
    void removeState(unsigned id);

    /**
     * @brief Changes current state to ID
     * @param id unsigned int state id in controller
     */
    void changeState(unsigned id);

    /**
     * @brief Returns ID of state with given name, -1 if not found
     * @param name stirng state name
     */
    int stateID(std::string name) const;
};

} // namespace Core

#endif //_CORE_ANIMATION_CONTROLLER_HPP_
