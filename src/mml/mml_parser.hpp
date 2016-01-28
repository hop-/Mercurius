#ifndef _MML_MMLPARSER_HPP
#define _MML_MMLPARSER_HPP

#include <string>

namespace MML
{

class MMLParser
{
private:
    static MMLParser* m_instance;

public:
    static MMLParser* getInstance();

public:
    MMLParser();
    ~MMLParser();

public:
    bool parseFile(const std::string&);

private:
    void removeSpaceses(std::string&);

private:
    MMLParser(const MMLParser&) = delete;
    MMLParser& operator=(const MMLParser&) = delete;
};

} // namespace MML

#endif // _MML_MMLPARSER_HPP
