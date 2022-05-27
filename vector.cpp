// Copyright (c) 2022, The MaPra Authors.

#include "vector.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace mapra;

// =======================
//      Konstruktoren
// =======================

// ----- Konstruktor -----

Vector::Vector(size_t len) : elems_(len, 0) {}

// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================

// ----- Schreib- und Lesezugriff auf Vektorelemente -----

double &Vector::operator()(size_t i)
{
  return elems_.at(i);
}

// ----- Lesezugriff auf Elemente konstanter Vektoren -----

double Vector::operator()(size_t i) const
{
  return elems_.at(i);
}

// =====================
//      Zuweisungen
// =====================

// ----- Zuweisungsoperator mit Addition "+=" ----

Vector &Vector::operator+=(const Vector &x)
{
#ifndef NDEBUG
  if (x.GetLength() != this->GetLength())
  {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif
  for (size_t i = 0; i < x.GetLength(); i++)
    (*this)(i) += x(i);
}

// ----- Zuweisungsoperator mit Subtraktion "-=" ----

Vector &Vector::operator-=(const Vector &x)
{
#ifndef NDEBUG
  if (x.GetLength() != this->GetLength())
  {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif
  for (size_t i = 0; i < x.GetLength(); i++)
    (*this)(i) -= x(i);
}

// ----- Zuweisungsoperator mit Multiplikation "*=" ----

Vector &Vector::operator*=(double c)
{
  for (size_t i = 0; i < this->GetLength(); i++)
    (*this)(i) *= c;
}

// ----- Zuweisungsoperator mit Divsion "/=" ----

Vector &Vector::operator/=(double c)
{
  for (size_t i = 0; i < this->GetLength(); i++)
    (*this)(i) /= c;
}

// ==============================
//      Vektorlaenge aendern
// ==============================

// ----- Vektorlaenge aendern -----

Vector &Vector::Redim(size_t l) { (*this).elems_.resize(l, 0); }

std::size_t Vector::GetLength() const { return elems_.size(); }

// ======================
//      Vektornormen
// ======================

// ----- Euklidische Norm -----

double Vector::Norm2() const
{
  double sum = 0;
  for (size_t i = 0; i < this->GetLength(); i++)
    sum += (*this)(i) * (*this)(i);
  return sqrt(sum);
}

// ----- Maximum-Norm -----

double Vector::NormMax() const
{
  double max = (*this)(0);
  for (int i = 1; i < this->GetLength(); i++)
    if (max < (*this)(i))
      max = (*this)(i);
  return max;
}

// ==================================
//      arithmetische Operatoren
// ==================================

// ----- Addition "+" -----

Vector mapra::operator+(const Vector &x, const Vector &y)
{
#ifndef NDEBUG
  if (x.elems_.size() != y.elems_.size())
  {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif

  Vector z = x;
  return z += y;
}

// ----- Subtraktion "-" -----

Vector mapra::operator-(const Vector &x, const Vector &y)
{
#ifndef NDEBUG
  if (x.elems_.size() != y.elems_.size())
  {
    Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif

  Vector z = x;
  return z -= y;
}

// ----- Vorzeichen wechseln "-" -----

Vector mapra::operator-(Vector &x)
{
  Vector _x = x;
  _x *= -1;
  return _x;
}

// ----- Skalarprodukt "*" -----

double mapra::operator*(const Vector &x, const Vector &y)
{
#ifndef NDEBUG
  if (x.elems_.size() != y.elems_.size())
  {
    mapra::Vector::VecError("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
  }
#endif
  double sum = 0;
  for (unsigned int i = 0; i < x.elems_.size(); i++)
  {
    sum += x.elems_[i] * y.elems_[i];
  }
  return sum;
}

// ----- Multiplikation Skalar*Vektor "*" -----

Vector operator*(double c, const Vector &x)
{
  Vector cx = x;
  cx *= c;
  return cx;
}

// ----- Multiplikation Vektor*Skalar "*" -----

Vector operator*(const Vector &x, double c)
{
  Vector cx = x;
  cx *= c;
  return cx;
}

// ----- Division Vektor/Skalar "/" -----

Vector operator/(const Vector &x, double c)
{
  Vector div = x;
  div /= c;
  return div;
}

// ==============================
//      Vergleichsoperatoren
// ==============================

// ----- Test auf Gleichheit "==" -----

bool mapra::operator==(const Vector &x, const Vector &y)
{
  if (x.elems_.size() != y.elems_.size())
  {
    return false;
  }

  for (size_t i = 0; i < x.elems_.size(); i++)
  {
    if (x(i) != y(i))
    {
      return false;
    }
  }

  return true;
}

// ----- Test auf Ungleichheit "!=" -----

bool operator!=(const Vector &x, const Vector &y)
{
  if (x == y)
    return false;
  else
    return true;
}

// ==========================
//      Ein- und Ausgabe
// ==========================

// ----- Ausgabe "<<" -----

std::ostream &mapra::operator<<(std::ostream &s, const Vector &x)
{
  s << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.elems_.size(); i++)
  {
    s << "\n(" << std::setw(4) << i << ") " << x(i);
  }

  return s << std::endl;
}

// ----- Eingabe ">>" -----

std::istream &mapra::operator>>(std::istream &s, Vector &x)
{
  std::cout << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.elems_.size(); i++)
  {
    std::cout << "\n(" << std::setw(4) << i << ") " << std::flush;
    s >> x(i);
  }
  return s;
}

// ==========================
//      Fehlerbehandlung
// ==========================

// ----- Ausgabe der Fehlermeldung "str" -----

void Vector::VecError(const char str[])
{
  std::cerr << "\nVektorfehler: " << str << '\n'
            << std::endl;
  exit(1);
}
