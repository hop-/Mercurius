#ifndef _CORE_RENDERER_HPP_
#define _CORE_RENDERER_HPP_

#include "rectangle.hpp"

namespace Core
{

class GuiObject;
class Frame;

class Renderer
{
private:
    Frame* m_frame;
    Rectangle m_drawingArea;

public:
    /**
     * @brief Constructs Renderer for give frame
     * @param f pointer to Frame
     * @pre f should be valid pointer
     */
    Renderer(Frame* f);

public:
    /**
     * @brief Sets rect on which should be drawn objects,
     *        by default used frame sizes and (0, 0) position
     * @param rect drawing area
     */
    void setDrawingArea(Rectangle rect);

public:
    /**
     * @brief Interface for drawing GuiObject
     * @param g pointer of GuiObject
     * @pre g should be valid pointer
     */
    void drawObject(const GuiObject* g);

private:
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
};

} // end of namespace Core

#endif // _CORE_RENDERER_HPP_
