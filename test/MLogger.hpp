#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <queue>
#include <fstream>

class MLogger
{
public:
    MLogger();
    virtual ~MLogger();
    MLogger(const MLogger &src) = delete;
    MLogger &operator=(const MLogger &rhs) = delete;

    void log(std::string &entry);

private:
    void processEntries();
    void processEntriesHelper(std::queue<std::string> &queue, std::ofstream &ofs) const;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    std::queue<std::string> m_queue;
    std::thread m_thread;
    bool m_exit{false};
};