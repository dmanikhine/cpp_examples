#pragma once
#include <utility>

template <typename TLocalVector>
class TAction
{
public:
    TAction(){};
    virtual ~TAction(){};
    virtual std::pair<bool, TLocalVector> operator()() = 0;
    virtual void printLocalVector(TLocalVector &localVector) = 0;    
};