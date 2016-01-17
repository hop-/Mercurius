#ifndef _MML_MMLMANAGER_HPP
#define _MML_MMLMANAGER_HPP

#include <string>

namespace MML
{

class MMLRegistery;

class MMLManager
{
    static MMLManager* m_instance;

private:
    MMLRegistery* m_registery;    

public:
    static MMLManager* getInstance();

public:
    MMLManager();
    ~MMLManager();

public:
    bool parseMMLFile(const std::string&);

public:
    MMLRegistery* getRegistery();

private:
    MMLManager(const MMLManager&) = delete;
    MMLManager& operator=(const MMLManager&) = delete;
};

} // namespace MML

#endif // _MML_MMLMANAGER_HPP
