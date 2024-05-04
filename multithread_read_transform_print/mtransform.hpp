#include <thread>
#include <condition_variable>
#include <vector>
#include <string>
#include <utility>

using TLineString = std::pair<long,std::string>;
using TLineVectorInt = std::pair<long,std::vector<int>>;

class MTransform {
    public:
    MTransform();
    virtual ~MTransform();
    MTransform (const MTransform &src) = delete;
    MTransform &operator = (const MTransform &rhs) = delete;

    void readFile(std::ifstream &inFile);
    
    
    void transform();
    

    private:
    bool readPacket(std::ifstream &inFile);
    void printVector(std::vector<TLineString> prnVector);

    int transformVector(std::vector<TLineString> &tlineVector);

    long m_lineCounter {0};
    std::mutex m_inVectorMutex;

    std::thread m_transformThread;
    std::mutex m_transformVectorMutex;

    std::condition_variable m_transformCondVar;
    
    std::vector<TLineString> m_inVector;
    bool m_transformExit{false};

    std::thread m_collectThread;
    std::condition_variable m_collectCondVar;
    std::vector<TLineVectorInt> m_collectVector;
    bool m_collectExit{false};
};