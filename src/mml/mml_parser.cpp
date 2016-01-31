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

#include <iostream>

namespace MML
{

static const char open_bracket = '{';
static const char close_bracket = '}';
static const char open_value = ':';
static const char close_value = ';';

MMLParser* MMLParser::m_instance = 0;

MMLParser* MMLParser::
getInstance()
{
    if (m_instance == 0) {
        m_instance = new MMLParser();
    }
    return m_instance;
}

MMLParser::
MMLParser()
{
}

MMLParser::
~MMLParser()
{
}

bool MMLParser::
parseFile(const std::string& f)
{
    // TODO
    std::ifstream fin(f);
    std::string data((std::istreambuf_iterator<char>(fin)),
                 (std::istreambuf_iterator<char>()));
    removeSpaceses(data);
    if (!checkSyntax(data)) {
        // TODO throw exception
        throw "Syntax error";
    }
    std::cout<<data<<std::endl;
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
    char* buffer = new char[10];
    size_t s = tmp.copy(buffer, b);
    buffer[s] = '\0';
    std::cout<<buffer<<std::endl;
    std::string type(buffer);
    delete[] buffer;
    buffer = 0;
    tmp.erase(0, tmp.find_first_of(open_bracket));
    std::cout<<tmp<<std::endl;
    size_t i = 0;
    do {
        if (tmp[i] == open_bracket) {
            ++brackets;
        }
        if (tmp[i] == close_bracket) {
            --brackets;
        }
        ++i;
    } while(brackets != 0);
    std::cout<<i<<"\t"<<brackets<<std::endl;
    buffer = new char[i + 1];
    s = tmp.copy(buffer, i - 2 , 1);
    buffer[s] = '\0';
    std::string body(buffer);
    delete[] buffer;
    buffer = 0;
    tmp.erase(0, i);
    std::cout<<body<<std::endl;
    std::cout<<tmp<<std::endl;

    size_t fo = body.find_first_of(open_bracket);
    buffer = new  char[fo + 1];
    body.copy(buffer, fo);
    std::string tmp1(buffer);
    delete[] buffer;
    buffer = 0;
    size_t attr_end = tmp1.find_last_of(close_value);
    buffer = new char[attr_end + 1];
    s = tmp1.copy(buffer, attr_end + 1);
    buffer[s] = '\0';
    std::string attr(buffer);
    std::cout<<"ATTR: "<<attr<<std::endl;
    body.erase(0, attr_end + 1);
    std::cout<<body<<std::endl;
    MMLObject* level = parseMMLObject(type, attr);
    assert(0 != level);
//    parseObjects()

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
    std::cout<<name<<std::endl;
    attr_getter->getAttribute("name")->setValue<std::string>("attr_getter");
    std::cout<<attr_getter->getName()<<std::endl;
    delete attr_getter;
    MMLObject* level = createMMLObject(type, name);
    parseMMLAtribute(attr, level);
    return level;
}

void MMLParser::
parseGui(const std::string& gui, MMLObject* obj)
{
    if (gui.empty()) {
        return;
    }
    assert(0 != obj);
/*    MMLAttribute* g = obj->getAttribute("gui");
    assert(0 != g);*/
    std::string tmp = gui;
    size_t pos = tmp.find_first_of(open_bracket);
    tmp.erase(0, pos);
    tmp.erase(tmp.size() - 2 , 1);
//    parseMMLAtribute(tmp, g);
}

void MMLParser::
parseLogic(const std::string& logic, MMLObject* obj)
{
    if (logic.empty()) {
        return;
    }
    assert(0 != obj);
/*    MMLAttribute* l = obj->getAttribute("logic");
    assert(0 != l);*/
    std::string tmp = logic;
    size_t pos = tmp.find_first_of(open_bracket);
    tmp.erase(0, pos);
    tmp.erase(tmp.size() - 2 , 1);
//    parseMMLAtribute(tmp, l);
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
            std::cout<<"noooooooooooooo attr: "<<attr_name<<std::endl;
            return; //  throw;
        }
        std::string attr_value = tmp.substr(0, pos);
        tmp.erase(0, pos + 1);
        parseMMLValue(attr_value, attr);
    }
}

void MMLParser::
parseMMLValue(const std::string& attr_value, MMLAttribute* attr)
{
    assert(0 != attr);
    std::stringstream converter;
    switch (attr->getType()) {
    case 0:
        // STRING
        attr->setValue(attr_value);
        break;
    case 1:
        // INT
        converter<<attr_value;
        int vi;
        converter>>vi;
        attr->setValue(vi);
        break;
    case 2:
        // DOUBLE
        converter<<attr_value;
        double vd;
        converter>>vd;
        attr->setValue(vd);
        break;
    case 3:
        // BOOL
        attr->setValue(attr_value == "true" ? true : false);
        break;
    default:
        break;
    }
}

}
