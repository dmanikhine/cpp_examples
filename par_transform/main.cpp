#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <regex>

int main(int argc, char *argv[])
{
    std::ifstream inFile{"log.txt"};
    if (inFile.fail())
    {
        std::cerr << "Failed to open file log.txt !!!" << std::endl;
        return 1;
    }

    std::string inLine;
    std::vector<std::string> sVec;

    while (std::getline(inFile, inLine))
    {
        sVec.push_back(inLine);
    }

    std::vector<std::vector<int>> iVec(sVec.size());
    std::string search = "5";

    std::transform(std::execution::par, sVec.cbegin(), sVec.cend(),
                   iVec.begin(),
                   [search](std::string x)
                   {
                       std::vector<int> index_matches;
                       std::regex rx(search);
                       for (auto it = std::sregex_iterator(x.begin(), x.end(), rx);
                            it != std::sregex_iterator();
                            ++it)
                       {
                           index_matches.push_back(it->position());
                       }
                       return index_matches;
                   });

    std::for_each(iVec.cbegin(), iVec.cend(), [](const std::vector<int> &vec)
                  {
                    if (vec.empty()) return;
                    for (auto i: vec) std::cout << i << ' '; 
                    std::cout << "\n"; });
}