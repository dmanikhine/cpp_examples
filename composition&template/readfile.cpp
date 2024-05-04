#include "readfile.hpp"
#include "mytype.hpp"
#include <iostream>

std::pair<bool, TVectorLongString> TReadFile::operator()()
{
    std::string inLine;
    TVectorLongString localVector;    
    for (int i = 1; i <= 2; i++)
    {
        if (std::getline(m_ifs, inLine))
        {
            localVector.push_back(std::pair{++m_lineCounter, inLine});
        }
        else
        {
            return std::pair{false, localVector};
        }
    }
    return std::pair{true, localVector};
}

void TReadFile::printLocalVector(TVectorLongString &localVector)
{
    for (const auto &i : localVector)
        std::cout << i.first << ' ' << i.second << std::endl;
}