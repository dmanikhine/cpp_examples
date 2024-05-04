#include <thread>
#include <condition_variable>
#include <vector>
#include <string>
#include <utility>

using TLine = std::pair<long,std::string>;

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
    void printVector(std::vector<TLine> prnVector);

    long m_lineCounter {0};
    std::thread m_transformThread;
    std::thread m_outThread;
    std::mutex m_inVectorMutex;
    std::mutex m_outMutex;
    std::condition_variable m_transformCondVar;
    std::condition_variable m_outCondVar;
    std::vector<TLine> m_inVector;
    bool m_transformExit{false};
    bool m_outExit{false};
};