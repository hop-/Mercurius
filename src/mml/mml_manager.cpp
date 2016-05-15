#include "mml_manager.hpp"
#include "mml_parser.hpp"
#include "mml_registery.hpp"

#include "background.hpp"
#include "config.hpp"
#include "mml_box.hpp"
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
     , m_layer_registery(new MMLRegistery())
     , m_types()
{
    registerTypes();
}

MMLManager::
~MMLManager()
{
    cleanTypeRegistery();
    assert(0 != m_layer_registery);
    assert(0 != m_registery);
    std::vector<MMLObject*> layers;
    std::for_each(m_layer_registery->begin(),
                  m_layer_registery->end(),
                  [&](MMLObject* o) {
                        assert(0 != o);
                        layers.push_back(o);
                  });
    std::for_each(layers.begin(),
                  layers.end(),
                  [](MMLObject* o) {
                        assert(0 != o);
                        delete o;
                  });
    delete m_layer_registery;
    m_layer_registery = 0;
    delete m_registery;
    m_registery = 0;
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

MMLRegistery* MMLManager::
getLayerRegistery()
{
    return m_layer_registery;
}

}
