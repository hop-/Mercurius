#include "mml_manager.hpp"
#include "mml_parser.hpp"
#include "mml_registery.hpp"

#include "mml_box.hpp"
#include "mml_layer.hpp"

#include <algorithm>
#include <utility>

namespace MML
{

MMLManager* MMLManager::m_instance = 0;

MMLManager* MMLManager::
getInstance()
{
    if (m_instance == 0) {
        m_instance = new MMLManager();
    }
    return m_instance;
}

MMLManager::
MMLManager()
     : m_registery(new MMLRegistery())
{
    registerTypes();
}

MMLManager::
~MMLManager()
{
    cleanTypeRegistery();
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
