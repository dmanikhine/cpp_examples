#pragma once
#include "taction.hpp"
#include "helplock.hpp"
#include <thread>

#include <iostream>


template <typename TMasterVector>
class TMasterThread
{
public:
    std::thread m_thread;
    THelpLock &m_hl;
    TMasterVector m_masterVector;
    
    TMasterAction<TMasterVector> &m_masterAction;
    
    TMasterThread(TMasterAction<TMasterVector> &masterAction, THelpLock &helpLock):
     m_masterAction{masterAction},
     m_hl{helpLock} {
        m_thread=std::thread(&TMasterThread::test, this);
    };

    ~TMasterThread(){               
        m_thread.join();
    }
    void test()
    {                
        while (true)
        {           
            std::unique_lock lock{m_hl.m_mutex};
            if (m_hl.m_masterSwapReady){
                m_hl.m_condVar.wait(lock);
            }
                        
            std::pair<bool, TMasterVector> result = m_masterAction();            

            m_masterVector=result.second; //I am sure we have here move semantic....
            //m_masterAction.printMasterVector(result.second);

            if (!result.first) {
                m_hl.m_masterSwapReady=true;  
                m_hl.m_condVar.notify_all();
                m_hl.m_exit = true;
                break;            
            }
            m_hl.m_masterSwapReady=true;            
            m_hl.m_condVar.notify_all();            
        }
    };
};