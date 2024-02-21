#include <iostream>
#include <regex>

int main(int argc, char *argv[]){
std::string str = "ababababababab";
std::regex rx("abab");

std::vector<int> index_matches; // results saved here 
                           // (should be {2, 8}, but always get only {2})

for(auto it = std::sregex_iterator(str.begin(), str.end(), rx);
    it != std::sregex_iterator();
     ++it)
{
    index_matches.push_back(it->position());
    std::cout<<it->position()<<std::endl;
}
}
