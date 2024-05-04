#pragma once
#include "taction.hpp"

template <typename TLocalVector>
class TWrapThread
{
public:
    TAction<TLocalVector> &m_threadAction;
    TWrapThread<TLocalVector>(TAction<TLocalVector> &threadAction) : m_threadAction{threadAction} {};
    void test()
    {
        while (true)
        {
            std::pair<bool, TLocalVector> result = m_threadAction();
            if (!result.first)
            {
                m_threadAction.printLocalVector(result.second);
                break;
            }
            m_threadAction.printLocalVector(result.second);
        }
    };
};