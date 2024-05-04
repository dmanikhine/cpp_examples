#pragma once
#include "taction.hpp"
#include "helplock.hpp"
#include <vector>
#include <thread>

template <typename TMasterVector, typename TSlaveVector>
class TSlaveThread
{
public:
    std::thread m_thread;
    THelpLock &m_hl;

    TMasterVector &m_masterVector;
    TSlaveVector m_slaveVector;

    TSlaveAction<TMasterVector, TSlaveVector> &m_slaveAction;

    TSlaveThread(TMasterVector &masterVector, TSlaveAction<TMasterVector, TSlaveVector> &slaveAction, THelpLock &helpLock) : m_masterVector{masterVector},
                                                                                                                             m_slaveAction{slaveAction},
                                                                                                                             m_hl{helpLock}
    {
        m_thread = std::thread(&TSlaveThread::thread_action, this);
    };

    ~TSlaveThread()
    {
        m_thread.join();
    }
    void thread_action()
    {

        while (true)
        {
            if (m_hl.m_exit)
            {
                std::pair<bool, TSlaveVector> result = m_slaveAction(m_masterVector);
                m_slaveVector = result.second; // I am sure we have here move semantic....
                m_slaveAction.printSlaveVector(result.second);
                break;
            }

            std::unique_lock lock{m_hl.m_mutex};
            if (!m_hl.m_masterSwapReady)
            {
                std::cout << "Slave wait for Master" << std::endl;
                m_hl.m_condVar.wait(lock);
                
            }

            TMasterVector masterVector;
            masterVector.swap(m_masterVector);
            std::cout << "Slave after swap!" << std::endl;
            m_hl.m_masterSwapReady=false;
            m_hl.m_condVar.notify_all();
            lock.unlock();
            
            std::pair<bool, TSlaveVector> result = m_slaveAction(masterVector);
            m_slaveVector = result.second; // I am sure we have here move semantic....
            m_slaveAction.printSlaveVector(result.second);
        }
    };
};