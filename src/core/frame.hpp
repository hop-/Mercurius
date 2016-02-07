#ifndef _CORE_FRAME_HPP_
#define _CORE_FRAME_HPP_

namespace Core
{

class Texture;

class Frame
{
    unsigned m_msPerUpdate;
    int m_width;
    int m_height;

protected:
    inline void setmsPerUpdate(const unsigned& ms)
    {
        m_msPerUpdate = ms;
    }

public:
    virtual ~Frame() = default;
    virtual void init() = 0;
    virtual void drawTexture(Texture* texture) = 0;
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
};

} // namespace Core

#endif //_CORE_FRAME_HPP_
