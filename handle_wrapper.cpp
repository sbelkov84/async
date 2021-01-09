#include <iostream>

#include "handle_wrapper.h"

THandleWrapper::THandleWrapper(std::size_t bulk)
{
  IsProcessing = true; 
  BulkManager = std::make_shared<TBulkManager>();
  FixedBulk = std::make_shared<TSingleBulk>(BulkManager.get(), eBulkTypeFixed, (int) bulk);
  DynamicBulk = std::make_shared<TSingleBulk>(BulkManager.get(), eBulkTypeDynamic);
  
  Thread = std::make_unique<std::thread>(&THandleWrapper::makeJob, this);
}

THandleWrapper::~THandleWrapper()
{
  StopProcessing();
  if (Thread.get()->joinable())
    Thread.get()->join();
}

void THandleWrapper::AddReceivedData(const char* data, std::size_t size)
{
  std::unique_lock<std::mutex> Lock(Mtx);
  qCmds.push(TQEl{std::string(data), size});
  Lock.unlock();
}

void THandleWrapper::AddQuitCmd()
{
  std::unique_lock<std::mutex> Lock(Mtx);
  qCmds.push(TQEl{std::string("quit"), -1});
  Lock.unlock();
}

void THandleWrapper::makeJob()
{  
  std::mutex locMtx;
  while (true)
  {
    if (!qCmds.empty())
    {
      std::unique_lock<std::mutex> Lock(locMtx);
      TQEl In = qCmds.front();
      qCmds.pop();
      Lock.unlock();
      
      if (In.first == "quit" && In.second == -1)
        break;
    
      ExecCmds(In);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  
  //  остылек, если осталась невыполненна€ команда 
  BulkManager.get()->ExecCmd(CurCmd);
}

void THandleWrapper::ExecCmds(TQEl& In)
{
  std::size_t i = 0; 
  
  while (i < In.second)
  {     
    if (In.first[i] == '\n')
    {
      if (!CurCmd.empty() && CurCmd != "\n") 
      {
        BulkManager.get()->ExecCmd(CurCmd);
      }

      CurCmd.clear();
    }
    else
    {  
      CurCmd.append(1, In.first[i]);      
    }
        
    ++i;
  }
}

void THandleWrapper::StopProcessing()
{
  AddQuitCmd();
}
