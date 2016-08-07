#include "animation_controller.hpp"
#include "animation_state.hpp"
#include "game.hpp"

#include <cassert>

namespace Core
{

void AnimationController::
addState(AnimationState* state)
{
    assert(0 != state);
    m_states.push_back(state);
}

void AnimationController::
removeState(std::string name)
{
    int id = stateID(name);
    if (id < 0) {
        return;
    }
    removeState(id);
}

void AnimationController::
changeState(std::string name)
{
    int id = stateID(name);
    if (id < 0) {
        return;
    }
    changeState(id);
}

void AnimationController::
update()
{
    m_states[m_currentState]->update(Game::getTicks());
    // TODO add updateing of texture
}

void AnimationController::
removeState(unsigned id)
{
    if (id >= m_states.size()) {
        return;
    }
    m_states.erase(m_states.begin() + id + 1);
    if (m_currentState >= m_states.size()) {
        m_currentState = m_states.size() - 1;
    }
}

void AnimationController::
changeState(unsigned id)
{
    if (id >= m_states.size()) {
        return;
    }
    m_currentState = id;
}

int AnimationController::
stateID(std::string name) const
{
    for (unsigned id = 0; id < m_states.size(); ++id) {
        if (m_states[id]->name() == name) {
            return id;
        }
    }
    return -1;
}

} // namespace Core
