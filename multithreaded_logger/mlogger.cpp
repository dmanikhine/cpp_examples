#include "mlogger.hpp"
#include <fstream>
#include <iostream>

MLogger::MLogger()
{
    m_thread = std::thread{&MLogger::processEntries, this};
}

MLogger::~MLogger()
{
    {
        std::unique_lock lock{m_mutex};
        m_exit = true;
    }

    m_condVar.notify_all();
    m_thread.join();
    
}

void MLogger::log(std::string & entry)
{
    std::unique_lock lock{m_mutex};
    m_queue.push(std::move(entry));
    m_condVar.notify_all();
}

void MLogger::processEntries()
{
    std::ofstream logFile{"log.txt"};
    if (logFile.fail())
    {
        std::cerr << "Failed to open logfile." << std::endl;
        return;
    }

    std::unique_lock lock{m_mutex, std::defer_lock};

    while (true)
    {
        lock.lock();
        if (!m_exit)
        {
            m_condVar.wait(lock);
        }
        else
        {
            processEntriesHelper(m_queue, logFile);
            break;
        }

        std::queue<std::string> localQueue;
        localQueue.swap(m_queue);
        lock.unlock();
        processEntriesHelper(localQueue, logFile);
    }
}

void MLogger::processEntriesHelper(std::queue<std::string> &queue, std::ofstream &ofs) const
{
    while (!queue.empty())
    {
        ofs << queue.front() << std::endl;
        queue.pop();
    }
}