#include "exceptions.hpp"
#include "mml_parser.hpp"
#include "mml_attribute.hpp"
#include "mml_manager.hpp"

#include <cassert>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <stack>

namespace MML
{

static const char open_bracket = '{';
static const char close_bracket = '}';
static const char open_value = ':';
static const char close_value = ';';
static const char comma_value = ',';

template<>
MMLParser* Base::Singleton<MMLParser>::m_s_instance = 0;

MMLParser::
MMLParser()
    : Base::Singleton<MMLParser>()
{
}

MMLParser::
~MMLParser()
{
}

bool MMLParser::
parseFile(const std::string& f)
{
    std::ifstream fin(f);
    std::string data((std::istreambuf_iterator<char>(fin)),
                 (std::istreambuf_iterator<char>()));
    removeSpaceses(data);
    if (!checkSyntax(data)) {
        throw MMLSyntaxError();
    }
    parseLayers(data);
    return true;
}

void MMLParser::
removeSpaceses(std::string& string)
{
    string.erase(std::remove_if(
                    string.begin(), string.end(), 
                    [](char c){ return std::isspace(c);}), string.end());
}

bool MMLParser::
checkSyntax(const std::string& data)
{
    std::stack<char> symbols;
    for (std::string::size_type i = 0; i < data.size(); ++i) {
        if (data[i] == open_bracket) {
            symbols.push(data[i]);
            continue;
        }
        if (data[i] == close_bracket) {
            if (symbols.empty() || symbols.top() != open_bracket) {
                return false;
            }
            symbols.pop();
            continue;
        }
        if (data[i] == open_value) {
            symbols.push(data[i]);
            continue;
        }
        if (data[i] == close_value) {
            if (symbols.empty() || symbols.top() != open_value) {
                return false;
            }
            symbols.pop();
            continue;
        }
    }
    if (!symbols.empty()) {
        return false;
    }
    return true;
}

MMLObject* MMLParser::
createMMLObject(const std::string& type, const std::string& name)
{
    MMLManager* m = MMLManager::getInstance();
    assert(0 != m);
    MMLManager::Factory* f = m->getTypeFactory(type);
    assert(0 != f);
    // TODO
    return f->create(name);
}

bool MMLParser::
isMetaSymbol(char c)
{
    return ((c == open_value) || (c == close_value) ||
            (c == open_bracket) || (c == close_bracket));
}

void MMLParser::
parseLayers(const std::string& data)
{
    std::string tmp = data;
    unsigned brackets = 0;
    size_t b = tmp.find_first_of(open_bracket);
    std::string type = tmp.substr(0, b);
    tmp.erase(0, tmp.find_first_of(open_bracket));
    size_t i = 0;
    do {
        if (tmp[i] == open_bracket) {
            ++brackets;
        }
        if (tmp[i] == close_bracket) {
            --brackets;
        }
        ++i;
    } while (brackets != 0);
    std::string body = tmp.substr(1, i - 2);
    tmp.erase(0, i);
    size_t fo = body.find_first_of(open_bracket);
    std::string tmp1 = body.substr(0, fo);
    size_t attr_end = tmp1.find_last_of(close_value);
    std::string attr = tmp1.substr(0, attr_end + 1);
    body.erase(0, attr_end + 1);
    MMLObject* level = parseMMLObject(type, attr);
    assert(0 != level);
    while(!body.empty()) {
        size_t obj_begin = body.find_first_of(open_bracket);
        std::string obj_type = body.substr(0, obj_begin);
        body.erase(0, obj_begin + 1);
        size_t obj_end = body.find_first_of(close_bracket);
        std::string obj_body = body.substr(0, obj_end);
        body.erase(0, obj_end + 1);
        MMLObject* child = parseMMLObject(obj_type, obj_body);
        assert(0 != child);
        child->setParent(level);
    }
    if (!tmp.empty()) {
        parseLayers(tmp);
    }
}

MMLObject* MMLParser::
parseMMLObject(const std::string& type, const std::string& attr)
{
    // Workaround for getting name attribute
    MMLObject* attr_getter = createMMLObject(type, "attr_getter");
    parseMMLAtribute(attr, attr_getter);
    const std::string name = attr_getter->getName();
    attr_getter->getAttribute("name")->setValue<std::string>("attr_getter");
    delete attr_getter;
    MMLObject* level = createMMLObject(type, name);
    parseMMLAtribute(attr, level);
    return level;
}

void MMLParser::
parseMMLAtribute(const std::string& attributes, MMLObject* obj)
{
    if (attributes.empty()) {
        return;
    }
    assert(0 != obj);
    std::string tmp = attributes;
    while (!tmp.empty()) {
        size_t pos = tmp.find_first_of(open_value);
        if (pos == std::string::npos) {
            return; //  throw
        }
        std::string attr_name = tmp.substr(0, pos);
        tmp.erase(0, pos + 1);
        pos = tmp.find_first_of(close_value);
        if (pos == std::string::npos) {
            return; //  throw
        }
        MMLAttribute* attr = obj->getAttribute(attr_name);
        if (attr == 0) {
            throw MMLNoAttribute(obj->getType(), attr_name);
        }
        std::string attr_value = tmp.substr(0, pos);
        tmp.erase(0, pos + 1);
        parseMMLValue(attr_value, attr);
    }
}

namespace {

template <typename T>
T convertto(const std::string& v)
{
    std::stringstream converter;
    converter<<v;
    T vi;
    converter>>vi;
    return vi;
}

MMLAttribute::IntPair toIntPair(const std::string& v)
{
    int cp = v.find_first_of(comma_value);
    std::string first = v.substr(0, cp);
    std::string second = v.substr(cp + 1, v.size());
    return MMLAttribute::IntPair(convertto<int>(first),
                                 convertto<int>(second));
}

}

void MMLParser::
parseMMLValue(const std::string& attr_value, MMLAttribute* attr)
{
    assert(0 != attr);
    switch (attr->getType()) {
    case 0:
        // STRING
        attr->setValue(attr_value);
        break;
    case 1:
        // INT
        attr->setValue(convertto<int>(attr_value));
        break;
    case 2:
        // DOUBLE
        attr->setValue(convertto<double>(attr_value));
        break;
    case 3:
        // BOOL
        attr->setValue(attr_value == "true" ? true : false);
        break;
    case 4:
        // IntPair
        attr->setValue(toIntPair(attr_value));
        break;
    default:
        break;
    }
}

}
