#include "animation_state.hpp"

namespace Core
{

AnimationState::
AnimationState(const std::string& name)
    :m_name(name)
    , m_beginPositionInTexture(0, 0)
{}

std::string AnimationState::
name() const
{
    return m_name;
}

void AnimationState::
update(unsigned ticks)
{
    if (!isLooped() && m_currentFrame == m_frames - 1) {
        return;
    }
    unsigned deltaTicks = ticks - m_previousTicks;
    m_previousTicks = ticks;
    int framesToPass = deltaTicks / m_frameDelay;
    nextState(framesToPass);
}

void AnimationState::
setBeginPosition(unsigned x, unsigned y)
{
    m_beginPositionInTexture = BeginPosition(x, y);
}

void AnimationState::
setNumberOfFrames(unsigned n)
{
    m_frames = n;
}

unsigned AnimationState::
numberOfFrames() const
{
    return m_frames;
}

unsigned AnimationState::
currentFrame() const
{
    return m_currentFrame;
}

void AnimationState::
setLoop(bool l)
{
    m_isloop = l;
}

bool AnimationState::
isLooped() const
{
    return m_isloop;
}

void AnimationState::
setCountOfCycles(unsigned count)
{
    m_cycleCount = count;
}

void AnimationState::
setFrameRate(unsigned fps)
{
    m_frameDelay = 1000 / fps;
}

void AnimationState::
nextState(unsigned n)
{
    if (n == 0) {
        return;
    }
    m_currentFrame += n;
    if (m_currentFrame < m_frames) {
        return;
    }
    if (isLooped()) {
        m_currentFrame = m_frames - m_currentFrame - 1;
    } else {
        m_currentFrame = m_frames - 1;
    }
}

} // namespace Core
