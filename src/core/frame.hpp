#ifndef _CORE_FRAME_HPP_
#define _CORE_FRAME_HPP_

namespace Core
{

class Texture;

class Frame
{
    unsigned m_msPerUpdate;

protected:
    inline void setmsPerUpdate(const unsigned& ms)
    {
        m_msPerUpdate = ms;
    }
    
public:
    virtual ~Frame() = default;
    virtual void init() = 0;
    virtual void drawTexture(Texture* texture) = 0;

    inline const unsigned& msPerUpdate() const
    {
        return m_msPerUpdate;
    }
};

} // namespace Core

#endif //_CORE_FRAME_HPP_
