#pragma once
#include <fstream>
#include "mytype.hpp"
#include "taction.hpp"

class TTransformLine : public TSlaveAction<TVectorLongString, TVectorLongInt>
{
public:
    TTransformLine(){}; 

    std::pair<bool, TVectorLongInt> operator()(TVectorLongString &masterVector) override;
    virtual void printSlaveVector(TVectorLongInt &slaveVector);

private:    
    
};