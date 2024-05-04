#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

class MLogger
{
public:
    MLogger();

    MLogger(const MLogger &src) = delete;
    MLogger &operator=(const MLogger &rhs) = delete;
    virtual ~MLogger();

    void log(std::string& entry);

private:
    void processEntries();
    void processEntriesHelper(std::queue<std::string> &queue, std::ofstream &ofs) const;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    std::queue<std::string> m_queue;
    std::thread m_thread;
    bool m_exit { false };
};
