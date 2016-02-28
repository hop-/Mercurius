#ifndef _CORE_FRAME_HPP_
#define _CORE_FRAME_HPP_

namespace Core
{

class GuiObject;

class Frame
{
    unsigned m_msPerUpdate;
    int m_width;
    int m_height;

public:
    Frame();
    virtual ~Frame() = default;

public:
    virtual void init() = 0;
    virtual void draw(GuiObject* object) = 0;
    virtual void setResolution(int width, int height);

    inline const int width() const
    {
        return m_width;
    }

    inline const int height() const
    {
        return m_height;
    }

    inline const unsigned& msPerUpdate() const
    {
        return m_msPerUpdate;
    }

    virtual void* renderer() const = 0;

protected:
    inline void setMsPerUpdate(const unsigned& ms)
    {
        m_msPerUpdate = ms;
    }
};

} // namespace Core

#endif //_CORE_FRAME_HPP_
