#include "pch.h"

#include "../WinAPIEngine/Vec3.h"
#include "../WinAPIEngine/Mat3.h"
#include "../WinAPIEngine/Vec3.cpp"
#include "../WinAPIEngine/Mat3.cpp"

#include "../WinAPIEngine/Calculator.h"
#include "../WinAPIEngine/Calculator.cpp"

//https://docs.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=vs-2019
//https://stackoverflow.com/questions/47515089/lnk2019-unresolved-external-symbol-in-vs-unit-testing


TEST(TestCalczOnPlane, ZZeroPlane) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);

  Vec3 c1(0, 0, 0);
  Vec3 c2(1, 0, 0);
  Vec3 c3(1, 1, 0);

  float x = 0.5f;
  float y = 0.5f;

  float calcZ = Calculator::zOnPlane(c1, c2, c3, x, y);

  EXPECT_EQ(calcZ, 0) << "Expected 0 but was: " << calcZ;

}