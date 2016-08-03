#ifndef _CORE_DRAWABLE_OBJECT_HPP_
#define _CORE_DRAWABLE_OBJECT_HPP_

#include "rectangle.hpp"

#include <string>

namespace Core
{

class DrawableObject
{
public:
    enum States {running, jumping, climbing}; // need to be reviewed

public:
    /**
     * @brief Constructer of drawable object
     * @param p path to the texture
     * @param w widht of texture
     * @param h height of texture
     * @param fw widht of frames in texture
     * @param fh height of frames in texture
     */
    DrawableObject(const std::string& p,
                   unsigned w, unsigned h,
                   unsigned fw, unsigned fh);

public:
    /// Return width of the texture
    unsigned width() const;

    /// Return height of the texture
    unsigned height() const;

public:
    /**
     * @brief Sets passed state positions 
     * @param s state for which to set positions
     * @param tx top x, real top x will be counted by m_frame_width * tx
     * @param ty top y, real top y will be counted by m_frame_height * ty
     * @param bx bottom x ...
     * @param by bottom y ...
     */
    void setStatePositions(States s,
                           unsigned tx,
                           unsigned ty,
                           unsigned bx,
                           unsigned by);

public:
    /**
     * @brief Return next frame rect for given state
     * @param s state for which to return next frame rect
     */
    Rectangle getNextFrameForState(States s);

private:
    const std::string m_path;
    unsigned m_texture_width;
    unsigned m_texture_height;
    unsigned m_frame_width;
    unsigned m_frame_height;
};

} // end of namespace Core

#endif // _CORE_DRAWABLE_OBJECT_HPP_
