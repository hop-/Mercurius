#ifndef _FRAME_HPP_
#define _FRAME_HPP_

namespace Core
{

class Texture;

class Frame
{
public:
    virtual void init() = 0;
    virtual void drawTexture(Texture* texture) = 0; // TODO Texture
};

} /// namespace Core

#endif //_FRAME_HPP_
