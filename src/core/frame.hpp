#ifndef _CORE_FRAME_HPP_
#define _CORE_FRAME_HPP_

#include <map>
#include <list>

namespace Core
{

class GuiObject;

class Frame
{
public:
    enum ScreenMode {fullScreen, window, fullScreenFit};

private:
    unsigned m_msPerUpdate;
    int m_width;
    int m_height;
    ScreenMode m_screenMode;
    std::map<const int, std::list<const GuiObject*> > m_sortedObjects; // need to descuse

public:
    Frame();
    virtual ~Frame() = default;

public:
    virtual void init() = 0;
    virtual void clear() = 0;
    void draw();
    void prepareToDraw(const GuiObject* object);
    virtual void setResolution(int width, int height);
    virtual void* renderer() const = 0;
    void setScreenMode(ScreenMode m);
    ScreenMode screenMode() const;

    inline int width() const
    {
        return m_width;
    }

    inline int height() const
    {
        return m_height;
    }

    inline const unsigned& msPerUpdate() const
    {
        return m_msPerUpdate;
    }

protected:
    virtual void show() = 0;
    virtual void draw(const GuiObject* object) = 0;
    inline void setMsPerUpdate(const unsigned& ms)
    {
        m_msPerUpdate = ms;
    }
};

} // namespace Core

#endif //_CORE_FRAME_HPP_
