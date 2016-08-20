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
     * @param column unsigned int position
     * @param row unsigned int position
     */
    void setFrame(unsigned column, unsigned row);

private:
    const std::string m_path;
    unsigned m_textureWidth;
    unsigned m_textureHeight;
    unsigned m_frameWidth;
    unsigned m_frameHeight;
    unsigned m_currentFrameColumn;
    unsigned m_currentFrameRow;
    unsigned m_maxColumns;
    unsigned m_maxRows;
};

} // end of namespace Core

#endif // _CORE_DRAWABLE_OBJECT_HPP_
