#include "wrapthread.hpp"
#include "readfile.hpp"
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
    TWrapThread<TVectorLongString> wt{rf};
    wt.test(); 
}