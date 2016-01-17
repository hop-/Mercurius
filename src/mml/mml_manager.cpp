#include "mml_manager.hpp"
#include "mml_registery.hpp"

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
}

MMLManager::
~MMLManager()
{
}

MMLRegistery* MMLManager::
getRegistery()
{
    return m_registery;
}

}
