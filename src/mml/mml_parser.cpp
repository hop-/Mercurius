#include "mml_parser.hpp"

#include <cctype>
#include <algorithm>
#include <fstream>
#include <streambuf>

#include <iostream>

namespace MML
{

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

}
