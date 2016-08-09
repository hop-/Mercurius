#ifndef _CORE_ANIMATION_STATE_HPP_
#define _CORE_ANIMATION_STATE_HPP_

#include <string>

namespace Core
{

class AnimationState
{
public:
    using Position = std::pair<unsigned, unsigned>;

private:
    const std::string m_name;
    Position m_beginPositionInTexture; // TODO need to be discused
    unsigned m_frames;
    unsigned m_currentFrame;
    bool m_isloop;
    unsigned m_cycleCount;
    unsigned m_frameDelay;
    unsigned m_previousTicks = 0;

public:
    /**
     * @brief Constructor to animation state
     * @param name const string reference name of animation state
     * @param beginPosition begin position of state in texture array
     * @param numberOfFrame unsigned number of frame
     * @param isLooped bool weather state looped or not
     * @param fps unsigned rate of frame
     */
    AnimationState(const std::string& name, Position beginPosition, unsigned numberOfFrame, bool isLooped, unsigned fps);

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
     * @brief Checks if state looped or not
     */
    bool isLooped() const;

    /**
     * @brief Sets count of cycles if not looped
     * @param count unsigned count of cycles
     */
    void setCountOfCycles(unsigned count);

private:
    void nextFrame(unsigned n);
};

} // namespace Core

#endif //_CORE_ANIMATION_STATE_HPP_
