#ifndef _MML_MMLPARSER_HPP
#define _MML_MMLPARSER_HPP

#include <base/singleton.hpp>

#include <string>

namespace MML
{

class MMLObject;
class MMLAttribute;

class MMLParser : public Base::Singleton<MMLParser>
{
private:
    MMLParser();
    ~MMLParser();

public:
    bool parseFile(const std::string&);

private:
    void removeSpaceses(std::string&);
    bool checkSyntax(const std::string&);
    MMLObject* createMMLObject(const std::string&, const std::string&);
    MMLObject* parseMMLObject(const std::string&, const std::string&);
    void parseMMLAtribute(const std::string&, MMLObject*);
    void parseMMLValue(const std::string&, MMLAttribute*);
    bool isMetaSymbol(char);
    void parseLayers(const std::string&);

private:
    MMLParser(const MMLParser&) = delete;
    MMLParser& operator=(const MMLParser&) = delete;

    friend class Base::Singleton<MMLParser>;
};

} // namespace MML

#endif // _MML_MMLPARSER_HPP
