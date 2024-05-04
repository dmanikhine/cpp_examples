#include "mtransform.hpp"
#include <fstream>
#include <iostream>


int main(int argc, char *argv[])
{  

    std::ifstream inFile("read.txt");
    if (inFile.fail())
    {
        std::cerr << "Failed to open file read.txt!";
        exit(1);
    
    }

    MTransform mtransform;
    std::this_thread::sleep_for (std::chrono::seconds(1));

    mtransform.readFile(inFile);    
}
