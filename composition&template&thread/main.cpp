#include "masterthread.hpp"
#include "slavethread.hpp"
#include "readfile.hpp"
#include "transformline.hpp"
#include "helplock.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{    
    std::ifstream ifs("log.txt");
    if (ifs.fail()) {
        std::cerr << "Failed to open file log.txt !" << std::endl;
        return 1;
    }    
    TReadFile rf{ifs};
    THelpLock lockReadFile;
    TMasterThread<TVectorLongString> masterReadFile{rf,lockReadFile};    

    TTransformLine tl;
    TSlaveThread<TVectorLongString,TVectorLongInt> slaveTransformLine{masterReadFile.m_masterVector,tl,lockReadFile};
    
}