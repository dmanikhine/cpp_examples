#pragma once
#include <mutex>
#include <condition_variable>

struct THelpLock{
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    bool m_exit{false};
    bool m_masterSwapReady{false};
};