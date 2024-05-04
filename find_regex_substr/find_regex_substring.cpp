#include <iostream>
#include <regex>

std::string escapeRegex(const std::string& input) {
    // Characters that need to be escaped in a regex pattern
    //const std::string specialChars = "\\.^$|?*+()[]{}";
    const std::string specialChars = "\\^$|?*+()[]{}";

    std::string escaped;
    for (char c : input) {
        if (specialChars.find(c) != std::string::npos) {
            escaped += '\\';
        }
        escaped += c;
    }
    return escaped;
}

int main(int argc, char *argv[]){
std::string str = "$$b1bab$$b2a$b$abab";
std::string escapedInput = escapeRegex("$$..");
std::regex rx{escapedInput};

std::vector<int> index_matches; 
for(auto it = std::sregex_iterator(str.begin(), str.end(), rx);
    it != std::sregex_iterator();
     ++it)
{
    index_matches.push_back(it->position());
    std::cout<<it->position()<< " " << it->str() << std::endl;
}
}
