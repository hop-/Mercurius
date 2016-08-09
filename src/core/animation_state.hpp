#ifndef _CORE_ANIMATION_STATE_HPP_
#define _CORE_ANIMATION_STATE_HPP_

#include <string>

namespace Core
{

class AnimationState
{
    using Position = std::pair<unsigned, unsigned>;

    const std::string m_name;
    Position m_beginPositionInTexture; // TODO need to be discused
    unsigned m_frames = 0;
    unsigned m_currentFrame = 0;
    bool m_isloop = true;
    unsigned m_cycleCount = 1;
    unsigned m_frameDelay = 1;
    unsigned m_previousTicks = 0;

public:
    /**
     * @brief Constructor to animation state
     * @param name const string reference name of animation state
     */
    AnimationState(const std::string& name);

    /**
     * @brief Virtual destructor to animation state
     */
    virtual ~AnimationState() = default;

public:
    /**
     * @brief Gets name of state
     */
    std::string name() const;

    /**
     * @brief Updates state
     * @param ticks unsigned ticks passed
     */
    virtual void update(unsigned ticks);

    /**
     * @brief Resets state
     */
    void reset(unsigned ticks);

public:
    /**
     * @brief Sets begin position
     * @param x unsigned int X position
     * @param y unsigned int Y position
     */
    void setPosition(unsigned x, unsigned y);

    /**
     * @brief Sets number of frames
     * @param n unsigned number of states
     */
    void setNumberOfFrames(unsigned n);

    /**
     * @brief Gets number of frames
     */
    unsigned numberOfFrames() const;

    /**
     * @brief Gets current frame
     */
    unsigned currentFrame() const;

    /**
     * @brief Gets position of current state in texture
     */
    Position currentFramePosition() const;

    /**
     * @brief Sets the state type (loop or not)
     */
    void setLoop(bool l);

    /**
     * @brief Checks if state looped or not
     */
    bool isLooped() const;

    /**
     * @brief Sets count of cycles if not looped
     * @param count unsigned count of cycles
     */
    void setCountOfCycles(unsigned count);

    /**
     * @brief Sets rate of frames
     * @param fps unsigned frame per second
     */
    void setFrameRate(unsigned fps);

private:
    /**
     * @brief Changes current state to the next state
     * @param n unsigned next n-th states;
     */
    void nextState(unsigned n);
};

} // namespace Core

#endif //_CORE_ANIMATION_STATE_HPP_
