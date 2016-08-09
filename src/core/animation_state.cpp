#include "animation_state.hpp"

namespace Core
{

AnimationState::
AnimationState(const std::string& name, Position beginPosition, unsigned numberOfFrames, bool isLooped, unsigned fps)
    :m_name(name)
    , m_beginPositionInTexture(beginPosition)
    , m_frames(numberOfFrames)
    , m_currentFrame(0)
    , m_isloop(isLooped)
    , m_cycleCount(1)
    , m_frameDelay(1000 / fps)
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
    nextFrame(framesToPass);
}

void AnimationState::
reset(unsigned ticks)
{
    m_currentFrame = 0;
    m_previousTicks = ticks;
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

AnimationState::Position AnimationState::
currentFramePosition() const
{
    Position p = m_beginPositionInTexture;
    p.second = p.second + m_currentFrame;
    return p;
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
nextFrame(unsigned n)
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
