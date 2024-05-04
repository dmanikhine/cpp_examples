#pragma once
#include <utility>

template <typename TMasterVector, typename TSlaveVector>
class TSlaveAction
{
public:
    TSlaveAction(){};
    virtual ~TSlaveAction(){};
    virtual std::pair<bool, TSlaveVector> operator()(TMasterVector &masterVector) = 0;
    virtual void printSlaveVector(TSlaveVector &slaveVector) = 0;
};

template <typename TMasterVector>
class TMasterAction
{
public:
    TMasterAction(){};
    virtual ~TMasterAction(){};
    virtual std::pair<bool, TMasterVector> operator()() = 0;
    virtual void printMasterVector(TMasterVector &masterVector) = 0;

private:
};