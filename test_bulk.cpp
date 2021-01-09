#include "single_bulk.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
//------------------------------------------------------------------------
const std::size_t gN = 5;
//------------------------------------------------------------------------

TEST(BULK, OnSpaceBulkEnding)
{
  std::string Printed;
  testing::internal::CaptureStdout();

  TBulkManager BulkManager;
  TSingleBulk FixedBulk(&BulkManager, eBulkTypeFixed, gN);
  TSingleBulk DynamicBulk(&BulkManager, eBulkTypeDynamic);

  BulkManager.ExecCmd("cmd1");
  BulkManager.ExecCmd("cmd2");
  BulkManager.ExecCmd("cmd3");
  BulkManager.ExecCmd("");
  
  std::string Etalon = "bulk: cmd1 cmd2 cmd3";

  Printed = testing::internal::GetCapturedStdout();
  EXPECT_EQ(Printed.compare(0, Etalon.length(), Etalon), 0);    
    
  testing::internal::CaptureStdout();
  BulkManager.ExecCmd("cmd4");
  BulkManager.ExecCmd("cmd5");
  BulkManager.ExecCmd("");
  
  Etalon = "bulk: cmd4 cmd5";
  Printed = testing::internal::GetCapturedStdout();
  EXPECT_EQ(Printed.compare(0, Etalon.length(), Etalon), 0);   
}
//------------------------------------------------------------------------

TEST(BULK, OnSpaceAndBraceEnding)
{
  std::string Printed;
  testing::internal::CaptureStdout();

  TBulkManager BulkManager;
  TSingleBulk FixedBulk(&BulkManager, eBulkTypeFixed, gN);
  TSingleBulk DynamicBulk(&BulkManager, eBulkTypeDynamic);

  BulkManager.ExecCmd("cmd1");
  BulkManager.ExecCmd("cmd2");
  BulkManager.ExecCmd("cmd3");
  BulkManager.ExecCmd("{");
  
  std::string Etalon = "bulk: cmd1 cmd2 cmd3";

  Printed = testing::internal::GetCapturedStdout();
  EXPECT_EQ(Printed.compare(0, Etalon.length(), Etalon), 0);    
    
  testing::internal::CaptureStdout();
  BulkManager.ExecCmd("cmd4");
  BulkManager.ExecCmd("cmd5");
  BulkManager.ExecCmd("cmd6");
  BulkManager.ExecCmd("cmd7");
  BulkManager.ExecCmd("}");
  
  Etalon = "bulk: cmd4 cmd5 cmd6 cmd7";
  Printed = testing::internal::GetCapturedStdout();
  EXPECT_EQ(Printed.compare(0, Etalon.length(), Etalon), 0);    
}
//------------------------------------------------------------------------

TEST(BULK, OnBraceInclusion)
{
  std::string Printed;
  testing::internal::CaptureStdout();

  TBulkManager BulkManager;
  TSingleBulk FixedBulk(&BulkManager, eBulkTypeFixed, gN);
  TSingleBulk DynamicBulk(&BulkManager, eBulkTypeDynamic);

  BulkManager.ExecCmd("{");
  BulkManager.ExecCmd("cmd1");
  BulkManager.ExecCmd("cmd2");
  BulkManager.ExecCmd("{");
  BulkManager.ExecCmd("cmd3");  
  BulkManager.ExecCmd("cmd4");
  BulkManager.ExecCmd("}");
  BulkManager.ExecCmd("cmd5");
  BulkManager.ExecCmd("cmd6");
  BulkManager.ExecCmd("}");

  std::string Etalon = "bulk: cmd1 cmd2 cmd3 cmd4 cmd5 cmd6";

  Printed = testing::internal::GetCapturedStdout();
  EXPECT_EQ(Printed.compare(0, Etalon.length(), Etalon), 0);
}
//------------------------------------------------------------------------

TEST(BULK, OnUnfinishedBulk)
{
  std::string Printed;
  testing::internal::CaptureStdout();
  TBulkManager BulkManager;
  TSingleBulk FixedBulk(&BulkManager, eBulkTypeFixed, gN);
  TSingleBulk DynamicBulk(&BulkManager, eBulkTypeDynamic);

  BulkManager.ExecCmd("cmd1");
  BulkManager.ExecCmd("cmd2");
  BulkManager.ExecCmd("cmd3");
  BulkManager.ExecCmd("{");  
  BulkManager.ExecCmd("cmd4");
  BulkManager.ExecCmd("cmd5");
  BulkManager.ExecCmd("cmd6");
  BulkManager.ExecCmd("cmd7");

  std::string Etalon = "bulk: cmd1 cmd2 cmd3";

  Printed = testing::internal::GetCapturedStdout();
  EXPECT_EQ(Printed.compare(0, Etalon.length(), Etalon), 0);
}
//------------------------------------------------------------------------

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  int Res = RUN_ALL_TESTS();
  return Res;
}
//------------------------------------------------------------------------
