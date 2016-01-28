#ifndef _MML_MMLPARSER_HPP
#define _MML_MMLPARSER_HPP

#include <string>

namespace MML
{

class MMLObject;
class MMLAttribute;

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
    bool checkSyntax(const std::string&);
    void matchMMLObject(const std::string&);
    void parseMMLObject(const std::string&);
    void parseMMLAtribute(const std::string&, MMLObject*);
    void parseMMLValue(const std::string&, MMLAttribute*);
    bool isMetaSymbol(char);

private:
    MMLParser(const MMLParser&) = delete;
    MMLParser& operator=(const MMLParser&) = delete;
};

} // namespace MML

#endif // _MML_MMLPARSER_HPP
