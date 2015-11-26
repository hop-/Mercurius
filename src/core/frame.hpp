#ifndef _FRAME_HPP_
#define _FRAME_HPP_

namespace Core
{

class Texture;

class Frame
{
    unsigned m_msPerUpdate;

protected:
    void setmsPerUpdate(unsigned ms);
    
public:
    virtual ~Frame() = default;
    virtual void init() = 0;
    virtual void drawTexture(Texture* texture) = 0; // TODO Texture
    const unsigned msPerUpdate() const;
};

} // namespace Core

#endif //_FRAME_HPP_
