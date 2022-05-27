#include "matrix.h"
#include "vector.h"
#include "unit.h"
#include <cstddef>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdlib>



std::tuple<mapra::Vector, double, int> power_series(const mapra::Matrix& A, mapra::Vector x_old, double eps){
  mapra::Vector x_new = (A*x_old);
  mapra::Vector x_new_s = x_new;
  mapra::Vector x_old_s;
  double lambda_new = x_new.NormMax();
  int k = 0;
  if(2 * std::abs(x_new(k)) <= lambda_new){
    for (size_t i=0; i < x_new.GetLength(); i++){
      if (std::abs(x_new(i)) == lambda_new )
        k = i;
    }
  }
  x_new = x_new/x_new(k);
  int counter = 2;
  double ew = x_new(k);

  do {
    x_old = x_new;
    x_new = A*x_old;
    ew = x_new(k);
    lambda_new = x_new.NormMax();
    x_old_s = x_new_s;
    x_new_s = x_new;
    if(2 * std::abs(x_new(k)) <= lambda_new){
      k = 0;
      for (size_t i=0; i < x_new.GetLength(); i++){
        if (std::abs(x_new(i)) == lambda_new )
          k = i;
      }
    }
    x_new = x_new/x_new(k);
    counter++;
  } while ((x_new-x_old).NormMax() > eps || std::abs(x_new_s(k)-x_old_s(k)) > eps);
  return std::make_tuple(x_new, ew, counter-1);
}



int main( int argc , char * argv []){
  std::cout << "-- TEST --" << std::endl<< std::endl;
  mapra::Matrix A(2,2);
  A(0,0) = 5;A(0,1) = 4;
  A(1,0) = 1;A(1,1) = 2;
//  for (int i=1; i<A.GetCols()+1; i++){
//    for (int j=1; j<A.GetRows()+1; j++){
//      A(j,i) = rand()%15 + 1;
//    }
//  }
  mapra::Vector v1(2);
  v1(0) = 1;v1(1) = 1;
  power_series(A, v1, 0.00001);

  std::cout << "TEST mit Getexample " << std::endl << std::endl;
  std::cout << "TEST argc " << argc << std::endl;

  int n = std::atoi(argv[1]);
  std::cout << "TEST argv " << n << std::endl;
  auto [B, x, eps] = mapra::GetExample(n);
  auto[v, lambda, c] = power_series(B, x, eps);
  mapra::CheckSolution(v, lambda, c);
}
