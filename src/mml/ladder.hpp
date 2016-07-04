#ifndef _MML_LADDER_HPP_
#define _MML_LADDER_HPP_

#include "object_array.hpp"

namespace MML
{

class Ladder
    : public ObjectArray
{
public:
    class Factory
        : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    Ladder(const std::string& n);
};

} // namespace MML

#endif //_MML_LADDER_HPP_
