#include "mlogger.hpp"
#include <vector>
#include <iostream>

void logSomeMessages(int id, MLogger &mlogger)
{
    for (int i{0}; i < 10; ++i)
    {
        std::string prefix = "Log entry "+std::to_string(i)+" ";
        std::string suffix = "from thread "+std::to_string(id);
        std::string logmessage = prefix + suffix;
        mlogger.log(logmessage);
    }
}
int main(int argc, char *argv[])
{
    MLogger mlogger;
    std::vector<std::thread> threads;
    // Create a few threads all working with the same Logger instance.
    

    for (int i{0}; i < 10; ++i)
    {
        threads.emplace_back(logSomeMessages, i, std::ref(mlogger));
    }
    // Wait for all threads to finish.
    
    for (auto &t : threads)
    {
        t.join();
    }     
}