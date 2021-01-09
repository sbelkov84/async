#ifndef handle_wrapper_h
#define handle_wrapper_h

#include <queue>
#include <memory>
#include <atomic>
#include <thread>
#include <mutex>

#include "single_bulk.h"

using TQEl = std::pair<std::string, std::size_t>;

class THandleWrapper
{
    std::atomic<bool> IsProcessing;
    std::string CurCmd;
    std::mutex Mtx;
    
    std::shared_ptr<TBulkManager> BulkManager;
    std::shared_ptr<TSingleBulk> FixedBulk;
    std::shared_ptr<TSingleBulk> DynamicBulk;
    
    std::unique_ptr<std::thread> Thread;
  
    std::queue<TQEl> qCmds;
    
    void makeJob();
    
    void ExecCmds(TQEl& In);
    void AddQuitCmd();
  
  public:
    THandleWrapper(std::size_t bulk);
    ~THandleWrapper();
    
    void AddReceivedData(const char* data, std::size_t size);
    void StopProcessing();
};

#endif