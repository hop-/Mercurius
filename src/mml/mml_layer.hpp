#ifndef _MML_MMLLAYER_HPP
#define _MML_MMLLAYER_HPP

#include "mml_object.hpp"

namespace MML
{

class MMLLayer
    : public MMLObject
{
public:
    class LayerFactory : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    MMLLayer(const std::string& n);
    virtual ~MMLLayer();
};

} // namespace MML

#endif // _MML_MMLLAYER_HPP
