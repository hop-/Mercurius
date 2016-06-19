#ifndef _CORE_FRAME_HPP_
#define _CORE_FRAME_HPP_

#include <list>
#include <map>

namespace Core
{

class GuiObject;

class Frame
{
public:
    enum class ScreenMode {fullScreen, window, fullScreenFit};
    enum class LayersViewMode {active, list, grid};

private:
    unsigned m_msPerUpdate;
    int m_width;
    int m_height;
    ScreenMode m_screenMode;
    LayersViewMode m_layersViewMode;

    typedef std::map<const int, std::list<const GuiObject*> > SortedObjects; // priority to objects
    SortedObjects m_sortedObjects;

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
    void setFPS(int fps);
    void setLayersViewMode(LayersViewMode m);
    LayersViewMode layersViewMode() const;

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

    inline void setWidth(int w)
    {
        m_width = w;
    }

    inline void setHeight(int h)
    {
        m_height = h;
    }
};

} // namespace Core

#endif //_CORE_FRAME_HPP_
