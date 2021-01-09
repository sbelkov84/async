#include <iostream>

#include "handle_wrapper.h"
#include "single_bulk.h"
#include "async.h"

namespace async {

handle_t connect(std::size_t bulk) {
  
  if (bulk <= 0)
  {
    std::cout << "Please set BulkSize cmd parameter greater than 0" << std::endl;
    return nullptr;
  }
  //---
  THandleWrapper* HWr = new THandleWrapper(bulk);
  //---
  
  return HWr;
}

void receive(handle_t handle, const char *data, std::size_t size) 
{
  ((THandleWrapper*) handle)->AddReceivedData(data, size);
}

void disconnect(handle_t handle) 
{  
  delete ((THandleWrapper*) handle);
}

}
