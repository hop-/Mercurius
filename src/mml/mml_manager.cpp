#include "mml_manager.hpp"
#include "mml_parser.hpp"
#include "mml_registery.hpp"

#include "background.hpp"
#include "config.hpp"
#include "mml_box.hpp"
#include "being.hpp"
#include "dude.hpp"
#include "door.hpp"
#include "switch.hpp"
#include "ground.hpp"
#include "platform.hpp"
#include "ladder.hpp"
#include "mml_layer.hpp"

#include <algorithm>
#include <utility>

namespace MML
{

template<>
MMLManager* Base::Singleton<MMLManager>::m_s_instance = 0;

MMLManager::
MMLManager()
     : Base::Singleton<MMLManager>()
     , m_registery(new MMLRegistery())
     , m_types()
{
    registerTypes();
}

MMLManager::
~MMLManager()
{
    cleanTypeRegistery();
    assert(0 != m_registery);
    std::vector<MMLLayer*> objects;
    m_registery->getObjects(objects);
    std::for_each(objects.begin(),
                  objects.end(),
                  [](MMLObject* o) {
                        assert(0 != o);
                        delete o;
                  });
    delete m_registery;
    m_registery = 0;
    objects.clear();
    assert(objects.empty());
    MMLParser::deleteInstance();
}

bool MMLManager::
loadData(const std::string& f)
{
    MMLParser* p = MMLParser::getInstance();
    assert(0 != p);
    return p->parseFile(f);
}

MMLManager::Factory* MMLManager::
getTypeFactory(const std::string& n)
{
    Types::iterator i = m_types.find(n);
    return i != m_types.end() ? i->second : 0;
}

void MMLManager::
registerTypes()
{
    // All types should be registerd in this function
    m_types["layer"] = new MMLLayer::LayerFactory();
    m_types["box"] = new MMLBox::BoxFactory();
    m_types["being"] = new Being::Factory();
    m_types["dude"] = new Dude::Factory();
    m_types["door"] = new Door::Factory();
    m_types["switch"] = new Switch::Factory();
    m_types["ground"] = new Ground::Factory();
    m_types["platform"] = new Platform::Factory();
    m_types["background"] = new Background::BackgroundFactory();
    m_types["ladder"] = new Ladder::Factory();
    m_types["config"] = new Config::Factory();
}

void MMLManager::
cleanTypeRegistery()
{
    std::for_each(m_types.begin(), m_types.end(),
                  [](Types::value_type& v) { delete v.second;});
    m_types.clear();
}

MMLRegistery* MMLManager::
getRegistery()
{
    return m_registery;
}

}
