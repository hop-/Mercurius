#ifndef _CORE_DRAWABLE_OBJECT_HPP_
#define _CORE_DRAWABLE_OBJECT_HPP_

#include "rectangle.hpp"

#include <string>

namespace Core
{

class DrawableObject
{
public:
    /**
     * @brief Constructer of drawable object
     * @param p path to the texture
     * @param w width of texture
     * @param h height of texture
     * @param fw width of frames in texture
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
     * @brief Sets frame
     * @param x position
     * @param y position
     */
    void setFrame(int x, int y);

private:
    const std::string m_path;
    unsigned m_texture_width;
    unsigned m_texture_height;
    unsigned m_frame_width;
    unsigned m_frame_height;
};

} // end of namespace Core

#endif // _CORE_DRAWABLE_OBJECT_HPP_
