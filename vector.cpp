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
  // ***** Hier fehlt was *****
}

// ----- Zuweisungsoperator mit Subtraktion "-=" ----

Vector &Vector::operator-=(const Vector &x)
{
  // ***** Hier fehlt was *****
}

// ----- Zuweisungsoperator mit Multiplikation "*=" ----

Vector &Vector::operator*=(double c)
{
  // ***** Hier fehlt was *****
}

// ----- Zuweisungsoperator mit Divsion "/=" ----

Vector &Vector::operator/=(double c)
{
  // ***** Hier fehlt was *****
}

// ==============================
//      Vektorlaenge aendern
// ==============================

// ----- Vektorlaenge aendern -----

Vector &Vector::Redim(size_t l)
{
  // ***** Hier fehlt was *****
}

std::size_t Vector::GetLength() const { return elems_.size(); }

// ======================
//      Vektornormen
// ======================

// ----- Euklidische Norm -----

double Vector::Norm2() const
{
  // ***** Hier fehlt was *****
}

// ----- Maximum-Norm -----

double Vector::NormMax() const
{
  // ***** Hier fehlt was *****
}

// ==================================
//      arithmetische Operatoren
// ==================================

// ----- Addition "+" -----

Vector operator+(const Vector &x, const Vector &y)
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

Vector operator-(const Vector &x, const Vector &y)
{
  // ***** Hier fehlt was *****
}

// ----- Vorzeichen wechseln "-" -----

Vector operator-(const Vector &x)
{
  // ***** Hier fehlt was *****
}

// ----- Skalarprodukt "*" -----

double operator*(const Vector &x, const Vector &y)
{
  // ***** Hier fehlt was *****
}

// ----- Multiplikation Skalar*Vektor "*" -----

Vector operator*(double c, const Vector &x)
{
  // ***** Hier fehlt was *****
}

// ----- Multiplikation Vektor*Skalar "*" -----

Vector operator*(const Vector &x, double c)
{
  // ***** Hier fehlt was *****
}

// ----- Division Vektor/Skalar "/" -----

Vector operator/(const Vector &x, double c)
{
  // ***** Hier fehlt was *****
}

// ==============================
//      Vergleichsoperatoren
// ==============================

// ----- Test auf Gleichheit "==" -----

bool operator==(const Vector &x, const Vector &y)
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
  // ***** Hier fehlt was *****
}

// ==========================
//      Ein- und Ausgabe
// ==========================

// ----- Ausgabe "<<" -----

std::ostream &operator<<(std::ostream &s, const Vector &x)
{
  s << std::setiosflags(std::ios::right);
  for (size_t i = 0; i < x.elems_.size(); i++)
  {
    s << "\n(" << std::setw(4) << i << ") " << x(i);
  }

  return s << std::endl;
}

// ----- Eingabe ">>" -----

std::istream &operator>>(std::istream &s, Vector &x)
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
