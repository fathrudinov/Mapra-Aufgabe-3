#include "matrix.h"
#include "vector.h"
#include <cmath>
#include <tuple>

using namespace mapra;


// Zur Matrix A soll dann mit Hilfe der Potenzmethode der betragsgroesste Eigenwert samt Eigenvektor bestimmt werden
std::tuple<Vector, double, int> power_series(const Matrix &A, Vector x_old, double eps)
{
  Vector x = x_old;       // Man startet die Potenzmethode mit einem beliebigen Vektor x_old
  Vector x_tilde = A * x; // \tilde x aus Aufgabenstellung
  size_t k = 0;           // man startet mit k = 1
  int64_t counter = 0;    // Anzahl der benötigten Iterationen
  double c = 2.0;         // eine (nicht zu grosse) Konstante, z. B. c = 2
  double EW;

  do
  {
    x_old = x;
    counter += 1;

    double NormMax = x_tilde.NormMax();
    if (c * std::abs(x_tilde(k)) <= NormMax) // man wählt k jeweils neu, wenn dies gilt, und zwar so, dass |x(k)| = x.NormMax()
      for (size_t i = 0; i < x.GetLength(); i++)
        if (std::abs(x_tilde(i)) == NormMax)
        {
          k = i;
          break;
        }

    x = x_tilde / x_tilde(k); // Da der Eigenvektor nur bis auf Vielfache bestimmt ist, kann man oBdA x(k) = 1 annehmen

    EW = x_tilde(k);

    x_tilde = A * x;

  } while ((x - x_old).NormMax() > eps || std::abs(EW - x_tilde(k)) > eps);

  return std::make_tuple(x, EW, counter);
}
