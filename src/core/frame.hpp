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
    int width() const;
    int height() const;
    const unsigned& msPerUpdate() const;

protected:
    virtual void show() = 0;
    virtual void draw(const GuiObject* object) = 0;
    void setMsPerUpdate(const unsigned& ms);
    void setWidth(int w);
    void setHeight(int h);
};

} // namespace Core

#endif //_CORE_FRAME_HPP_
