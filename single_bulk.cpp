//------------------------------------------------------------------------
#include "single_bulk.h"
//------------------------------------------------------------------------
#include <iostream>
#include <fstream>
//------------------------------------------------------------------------

TSingleBulk::TSingleBulk(TBulkManager* Manager, EBulkType Type, std::size_t N)
{
  Manager->Subscribe(this, Type);
  this->N = N;
}
//------------------------------------------------------------------------

void TSingleBulk::Print(std::ostream& Stream)
{
  if (Commands.size() == 0)
    return;
  //---
  Stream << "bulk: ";
  for (auto It = Commands.begin(); It != Commands.end(); ++It)
  {
    Stream << *It << " ";
  }
  Stream << std::endl;
}
//------------------------------------------------------------------------

void TSingleBulk::AddCmd(std::string& Cmd)
{
  if (Commands.empty())
    FirstCmdTime = std::time(nullptr);

  Commands.push_back(Cmd);
  if (N > 0 && Commands.size() == N)
    ReleaseBulk();
}
//------------------------------------------------------------------------

void TSingleBulk::ClearCmds()
{
  Commands.resize(0);
}
//------------------------------------------------------------------------

void TSingleBulk::ReleaseBulk(bool NeedToPrint)
{
  if (NeedToPrint)
  {
    Print(std::cout);
    SaveToFile();
  }
  //---
  ClearCmds();
}
//------------------------------------------------------------------------

void TSingleBulk::SaveToFile()
{
  if (Commands.empty())
    return;
  //---
  std::string BulkTime = std::to_string(FirstCmdTime);
  std::string FileName = "./logs/bulk";
  FileName += BulkTime;
  FileName += ".log";
  std::ofstream OutFile(FileName, std::ios::binary);

  try
  {
    Print(OutFile);
  }
  catch (...)
  {
    OutFile.close();
  }
  OutFile.close();
}
//------------------------------------------------------------------------
