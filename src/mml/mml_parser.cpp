#include "mml_parser.hpp"
#include "mml_attribute.hpp"
#include "mml_manager.hpp"

#include <cassert>
#include <cctype>
#include <algorithm>
#include <fstream>
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


void MMLParser::
matchMMLObject(const std::string& type)
{
    MMLManager* m = MMLManager::getInstance();
    assert(0 != m);
    MMLManager::Factory* f = m->getTypeFactory(type);
    assert(0 != f);
    // TODO
}


bool MMLParser::
isMetaSymbol(char c)
{
    return ((c == open_value) || (c == close_value) ||
            (c == open_bracket) || (c == close_bracket));
}

void MMLParser::
parseMMLAtribute(const std::string& attributes, MMLObject* obj)
{
    if (attributes.empty()) {
        return;
    }
    std::string tmp = attributes;
    while (!tmp.empty()) {
        std::string::size_type pos = tmp.find_first_of(open_value);
        if (pos == std::string::npos) {
            return; //  throw
        }
        std::string attr_name = tmp.substr(0, pos - 1);
        tmp.erase(0, pos);
        pos = tmp.find_first_of(close_value);
        if (pos == std::string::npos) {
            return; //  throw
        }
        MMLAttribute* attr = obj->getAttribute(attr_name);
        if (attr == 0) {
            return; //  throw;
        }
        std::string attr_value = tmp.substr(0, pos - 1);
        tmp.erase(0, pos);
        parseMMLValue(attr_value, attr);
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
        attr->setValue(std::stoi(attr_value));
        break;
    case 2:
        // DOUBLE
        attr->setValue(std::stod(attr_value));
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
