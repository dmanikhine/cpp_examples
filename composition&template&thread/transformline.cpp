#include "transformline.hpp"
#include "mytype.hpp"
#include <iostream>

std::pair<bool, TVectorLongInt> TTransformLine::operator()(TVectorLongString &masterVector)
{
    std::string inLine;
    TVectorLongInt localVector;    

    for (const auto &i : masterVector)
    {
        localVector.push_back(std::pair(i.first,i.second.length()));
    }    
    return std::pair{true, localVector};
}

void TTransformLine::printSlaveVector(TVectorLongInt &slaveVector)
{
    for (const auto &i : slaveVector)
        std::cout << i.first << ' ' << i.second << std::endl;
}