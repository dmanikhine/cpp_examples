#pragma once
#include <fstream>
#include "mytype.hpp"
#include "taction.hpp"

class TReadFile: public TMasterAction<TVectorLongString>
{
    public:
    TReadFile(std::ifstream &ifs)
        : m_ifs{ifs}{}
    TReadFile(const TReadFile &src) = delete;
    TReadFile &operator=(const TReadFile &rhs) =delete;

    std::pair<bool, TVectorLongString> operator()() override;    
    virtual void printMasterVector(TVectorLongString &localVector);  
private:
    std::ifstream &m_ifs;
    long m_lineCounter=0;    
};