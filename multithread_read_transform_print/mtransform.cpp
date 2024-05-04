#include "mtransform.hpp"
#include <fstream>
#include <iostream>

MTransform::MTransform()
{
    m_transformThread = std::thread(&MTransform::transform, this);
}

MTransform::~MTransform()
{
    {
        std::unique_lock lock{m_inVectorMutex};
        m_transformExit = true;
    }

    m_transformCondVar.notify_all();
    m_transformThread.join();
}

void MTransform::readFile(std::ifstream &inFile)
{

    while (true)
    {
        std::unique_lock lock{m_inVectorMutex};
        
        if (!readPacket(inFile))
        {
            m_transformCondVar.notify_all();
            break;
        }
        m_transformCondVar.notify_all();
        m_transformCondVar.wait(lock);
    }
}

bool MTransform::readPacket(std::ifstream &inFile)
{
    std::string inLine;

    for (int i = 1; i <= 2; i++)
    {
        if (std::getline(inFile, inLine))
        {
            m_inVector.push_back(std::pair{++m_lineCounter, inLine});
        }
        else
        {
            return false;
        }
    }
    return true;
}

void MTransform::transform()
{
    while (true)
    {
        if (m_transformExit)
        {
            printVector(m_inVector);
            break;
        }
        std::unique_lock lock{m_inVectorMutex};
        std::cout << "transfer lock!" << std::endl;
        std::vector<TLineString> localVector;
        localVector.swap(m_inVector);
        m_transformCondVar.notify_all();
        m_transformCondVar.wait(lock);

        //printVector(localVector);
    }
}

int MTransform::transformVector(std::vector<TLineString> &tlineVector){

    std::vector

}