#pragma once
#include <fstream>
#include "mytype.hpp"
#include "taction.hpp"

class TReadFile: public TAction<TVectorLongString>
{
    public:
    TReadFile(std::ifstream &ifs)
        : m_ifs{ifs}{}
    //ReadFile(const ReadFile &src) = delete;
    //ReadFile &operator=(const ReadFile &rhs) =delete;

    std::pair<bool, TVectorLongString> operator()() override;
    virtual void printLocalVector(TVectorLongString &localVector);  
private:
    std::ifstream &m_ifs;
    long m_lineCounter=0;    
};