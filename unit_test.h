#include "matrix.h"
#include "vector.h"
#include "mapra_test.h"
#include <fstream>
#include <cmath>
#include "power_series.h"
#include "unit.h"

using namespace mapra;

void set_Konstant_Vector(Vector &A, double k)
{
  for (size_t i = 0; i < A.GetLength(); i++)
  {
    A(i) = k;
  }
}

class vector_tests
{
private:
  Vector v1;
  Vector v2;
  Vector v3;
  MapraTest Tests;

public:
  vector_tests() : v1(2), v2(5), v3(5), Tests("vector_tests")
  {
    v1(0) = 5;
    v1(1) = 10;
    set_Konstant_Vector(v2, 1.0);
    set_Konstant_Vector(v3, 2.0);
  }

  void test_operator_plus()
  {
    Tests.AssertEq("test_operator_plus", v2 + v2, v3);
  }
  void test_operator_minus()
  {
    Tests.AssertEq("test_operator_minus", v3 - v2, v2);
  }
  void test_operator_mult()
  {
    Tests.AssertEq("test_operator_mult", 2.0 * v2, v3);
  }
  void test_operator_div()
  {
    Tests.AssertEq("test_operator_div", v3 / 2.0, v2);
  }
  void test_operator_Norm2()
  {
    Tests.AssertEq("test_operator_Norm2", v2.Norm2(), sqrt(5.0));
  }
  void test_operator_NormMax()
  {
    Tests.AssertEq("test_operator_NormMax ", v1.NormMax(), 10.0);
  }
  void Summary()
  {
    test_operator_plus();
    test_operator_minus();
    test_operator_mult();
    test_operator_div();
    test_operator_Norm2();
    test_operator_NormMax();
  }
};

class matrix_tests
{
private:
  Vector v, A_mal_v;
  Matrix A, zwei_mal_A;
  MapraTest Tests;

public:
  matrix_tests() : v(5), A_mal_v(5), A(5, 5), zwei_mal_A(5, 5), Tests("matrix_tests")
  {
    std::ifstream fin1, fin2, fin3;
    fin1.open("test_5x5.txt");
    fin1 >> A;

    fin2.open("test_5x1.txt");
    fin2 >> A_mal_v;

    fin3.open("test_5x5_2.txt");
    fin3 >> zwei_mal_A;

    set_Konstant_Vector(v, 1);
  }

  void test_operator_plus()
  {
    Tests.AssertEq("test_operator_plus", A + A, zwei_mal_A);
  }
  void test_operator_minus()
  {
    Tests.AssertEq("test_operator_minus", zwei_mal_A - A, A);
  }
  void test_operator_mult_scalar()
  {
    Tests.AssertEq("test_operator_mult_scalar", 2 * A, zwei_mal_A);
  }
  void test_operator_mult()
  {
    Tests.AssertEq("test_operator_mult", A * v, A_mal_v);
  }
  void test_operator_div()
  {
    Tests.AssertEq("test_operator_div", zwei_mal_A / 2, A);
  }
  void Summary()
  {
    test_operator_plus();
    test_operator_minus();
    test_operator_mult_scalar();
    test_operator_mult();
    test_operator_div();
  }
};

void power_series_tests()
{
  int n = 1;
  
  std::cout << "I am here1\n";
  auto [B, x, eps] = mapra::GetExample(n);
  std::cout << "I am here2\n";

  auto [v, lambda, c] = power_series(B, x, eps);
  mapra::CheckSolution(v, lambda, c);
}
