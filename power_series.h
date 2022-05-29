#include "matrix.h"
#include "vector.h"
#include <cmath>
#include <tuple>

std::tuple<mapra::Vector, double, int> power_series(const mapra::Matrix &A, mapra::Vector x_old, double eps)
{
  
  mapra::Vector x_new = (A * x_old);
  mapra::Vector x_new_s = x_new;
  mapra::Vector x_old_s;
  double lambda_new = x_new.NormMax();
  int k = 0;
  
  if (2 * std::abs(x_new(k)) <= lambda_new)
  {
    for (size_t i = 0; i < x_new.GetLength(); i++)
    {
      if (std::abs(x_new(i)) == lambda_new)
        k = i;
    }
  }
  x_new = x_new / x_new(k);
  int counter = 2;
  double ew = x_new(k);

  do
  {
    x_old = x_new;
    x_new = A * x_old;
    ew = x_new(k);
    lambda_new = x_new.NormMax();
    x_old_s = x_new_s;
    x_new_s = x_new;
    if (2 * std::abs(x_new(k)) <= lambda_new)
    {
      k = 0;
      for (size_t i = 0; i < x_new.GetLength(); i++)
      {
        if (std::abs(x_new(i)) == lambda_new)
          k = i;
      }
    }
    x_new = x_new / x_new(k);
    counter++;
  } while ((x_new - x_old).NormMax() > eps || std::abs(x_new_s(k) - x_old_s(k)) > eps);
  return std::make_tuple(x_new, ew, counter - 1);
}
