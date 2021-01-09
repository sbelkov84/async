#ifndef SINGLE_BULK_H
#define SINGLE_BULK_H
//------------------------------------------------------------------------
#include <vector>
#include <ctime>
//------------------------------------------------------------------------
#include "bulk_manager.h"
//------------------------------------------------------------------------

class TSingleBulk : public TBulkObserver
{
private:

  /*! Stores not-manage commands */
  /*! std::vector<std::string> Commands */
  std::vector<std::string> Commands;

  /*! \brief Maximal size of fixed bulk */
  /*! std::size_t N */
  std::size_t N;

  /*! \brief True if commands are adressed to this bulk */
  /*! bool IsActive */
  bool IsActive;

  /*! \brief Stores first command time in this bulk */
  /*! std::chrono::time_point<std::chrono::system_clock> */
  time_t FirstCmdTime;

  /*! \brief Prints this bulk in specified stream (stdout or file) */
  /*! void Print(std::ostream& Stream) */
  void Print(std::ostream& Stream);

  /*! \brief Saves bulk commands info into file */
  /*! void SaveToFile() */
  void SaveToFile();

public:

  /*! \brief Default constructor is used in child class */
  /*! TSingleBulk() */
  TSingleBulk() {N = 0;}

  /*! \brief Constructor sets default fields */
  /*! TFixedBulk(TBulkManager* Manager, EBulkType Type, std::size_t N) */
  TSingleBulk(TBulkManager* Manager, EBulkType Type, std::size_t N = 0);

  /*! \brief Adds cmd to commands-vector */
  /*! void AddCmd(std::string& Cmd) */
  void AddCmd(std::string& Cmd) override;

  /*! \brief Clears commands-vector */
  /*! void ClearCmds() */
  void ClearCmds();

  /*! \brief Sets IsActive variable */
  /*! void SetActive(bool Value) */
  void SetActive(bool Value);

  /*! \brief Print bulk in std::cout and file, clears command-vector */
  /*! void ReleaseBulk(bool NeedToPrint = true) */
  void ReleaseBulk(bool NeedToPrint = true) override;
};
//------------------------------------------------------------------------

#endif // SINGLE_BULK_H
