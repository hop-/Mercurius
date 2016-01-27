#include "mml_parser.hpp"

#include <fstream>

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
    std::fstream fin(f);
    std::string data;
    fin>>data;
    return true;
}

}
