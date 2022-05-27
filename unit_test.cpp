#include "matrix.h"
#include "vector.h"
#include "mapra_test.h"
#include <cstddef>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

void set_Konstant_Vector(mapra::Vector A, double k)
{
  for (unsigned int i = 0; i < A.GetLength(); i++)
  {
    A(i) = k;
  }
}

int main()
{

  mapra::Vector v1(5);
  mapra::Vector v2(5);
  mapra::Vector v3(5);
  mapra::Vector v4(5);
  set_Konstant_Vector(v1, 5);
  set_Konstant_Vector(v2, 3);
  set_Konstant_Vector(v3, 2);
  v3(1) = 4;
  v3(2) = 5;
  v3(4) = 1;

  std::cout << "\nTests:\n\n";
  std::cout << "Vector Operations:\n";
  std::cout << "v1:=\n"
            << v1 << "\n";
  std::cout << "v2:=\n"
            << v2 << "\n";
  std::cout << "v3:=\n"
            << v3 << "\n";
  std::cout << "v4:=\n"
            << v4 << "\n";
  std::cout << "v1 + v2:=\n"
            << v1 + v2 << "\n";
  std::cout << "v1 * v3:= " << v1 * v3 << "\n";
  std::cout << "v3 * 5:=\n"
            << v3 * 5 << "\n";
  std::cout << "redimension of v4 to 8:\n"
            << v4.Redim(8) << "\n";
  std::cout << "2-th norm of v1:= " << v1.Norm2() << "\n\n";
  std::cout << "Max-norm of v3:= " << v3.NormMax() << "\n\n";
  std::cout << "\nTest with mapra_test:\n";

  mapra::Vector test(5);
  test(0) = 8;
  test(1) = 8;
  test(2) = 8;
  test(3) = 8;
  test(4) = 8;
  mapra::MapraTest test9("Test1 v1 + v2: ");
  test9.AssertEq("test1", test, v1 + v2);
  mapra::MapraTest test1("Test2 v1 * v3: ");
  test1.AssertEq("test2", 70.0, v1 * v3);
  mapra::MapraTest test2("Test3 redim: ");
  size_t a = 8;
  test2.AssertEq("test3", a, v4.GetLength());
  mapra::MapraTest test3("Test4 Max.norm: ");
  test3.AssertEq("test4", 5.0, v3.NormMax());

  mapra::Matrix A1(2, 2);
  mapra::Matrix A2(2, 2);

  A1(0, 0) = 2;
  A1(0, 1) = -1;
  A1(1, 0) = 3;
  A1(1, 1) = 3;
  A2(0, 0) = 1;
  A2(0, 1) = 0;
  A2(1, 0) = -2;
  A2(1, 1) = 5;
  std::cout << "\n\nMatrix Operations:\n\n";
  std::cout << "A1:=\n"
            << A1 << "\n";
  std::cout << "A2:=\n"
            << A2 << "\n";
  std::cout << "A1 + A2:=\n"
            << A1 + A2 << "\n";
  std::cout << "A1 * A2:=\n"
            << A1 * A2 << "\n";
  std::cout << "A1 *= 3:=\n"
            << (A1 *= 3) << "\n";
  std::cout << "redimension of A2 to 5*3:\n"
            << A2.Redim(5, 3) << "\n";
  A2.Redim(2, 2);
  A1 /= 3;
  std::cout << "\n\nTest with mapra_test:\n";
  mapra::Matrix test_m2(2, 2);
  test_m2(0, 0) = 3;
  test_m2(0, 1) = -1;
  test_m2(1, 0) = 1;
  test_m2(1, 1) = 8;
  mapra::MapraTest test4("Test1 A1 + A2: ");
  test4.AssertEq("test1", test_m2, A1 + A2);
  test_m2(0, 0) = 4;
  test_m2(0, 1) = -5;
  test_m2(1, 0) = -3;
  test_m2(1, 1) = 15;
  mapra::MapraTest test5("Test2 A1 * A2: ");
  test5.AssertEq("test2", test_m2, A1 * A2);
  test_m2(0, 0) = 6;
  test_m2(0, 1) = -3;
  test_m2(1, 0) = 9;
  test_m2(1, 1) = 9;
  mapra::MapraTest test6("Test3 A1*=3: ");
  test6.AssertEq("test3", test_m2, (A1 *= 3));

  mapra::Vector v5(2);
  v5(0) = 2;
  v5(1) = 3;
  std::cout << "\n\nMatrix * Vector operations:\n\n";
  std::cout << "A:=\n"
            << (A1 /= 3) << "\n";
  std::cout << "v:=\n"
            << v5 << "\n";
  std::cout << "A*v:=\n"
            << A1 * v5 << "\n";
  std::cout << "transpose of v*A:=\n"
            << v5 * A1 << "\n";
  std::cout << "\n\nTest with mapra_test:\n";
  mapra::Vector test_v1(2);
  test_v1(0) = 1;
  test_v1(1) = 15;
  mapra::MapraTest test7("Test1 A * v: ");
  test7.AssertEq("test1", test_v1, A1 * v5);
  test_v1(0) = 13;
  test_v1(1) = 7;
  mapra::MapraTest test8("Test2 v * A: ");
  test8.AssertEq("test2", test_v1, v5 * A1);

  return 0;
}
