// Copyright (c) 2022, The MaPra Authors.

// Um keine grossen Geschwindigkeitseinbussen zu erleiden, 
// sollten Sie diese Überprüfung per Präprozessoranweisung #define NDEBUG abschalten können, 
// wenn Sie sicher sind, dass ihr Programm fehlerfrei läuft.

#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <iostream>
#include <vector>

#include "vector.h"

namespace mapra
{

  class Matrix
  {
  public:
    explicit Matrix(std::size_t r = 1, std::size_t c = 1);
    Matrix & operator=(const Matrix &);

    double &operator()(std::size_t, std::size_t);
    double operator()(std::size_t, std::size_t) const;

    Matrix &operator+=(const Matrix &);
    Matrix &operator-=(const Matrix &);
    Matrix &operator*=(const Matrix &);
    Matrix &operator*=(double);
    Matrix &operator/=(double);

    Matrix &Redim(std::size_t, std::size_t);
    std::size_t GetRows() const;
    std::size_t GetCols() const;

    static void MatError(const char str[]);

    friend Matrix operator+(const Matrix &, const Matrix &);
    friend Matrix operator-(const Matrix &, const Matrix &);
    friend Matrix operator-(const Matrix &);

    friend Matrix operator*(const Matrix &, const Matrix &);
    friend Matrix operator*(double, const Matrix &);
    friend Matrix operator*(const Matrix &, double);
    friend Matrix operator/(const Matrix &, double);

    friend bool operator==(const Matrix &, const Matrix &);
    friend bool operator!=(const Matrix &, const Matrix &);

    friend std::istream &operator>>(std::istream &, Matrix &);
    friend std::ostream &operator<<(std::ostream &, const Matrix &);

    friend Vector operator*(const Matrix &, const Vector &);
    friend Vector operator*(const Vector &, const Matrix &);

  private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<std::vector<double>> elems_;
  };

  Matrix operator+(const Matrix &, const Matrix &);
  Matrix operator-(const Matrix &, const Matrix &);
  Matrix operator-(const Matrix &);

  Matrix operator*(const Matrix &, const Matrix &);
  Matrix operator*(double, const Matrix &);
  Matrix operator*(const Matrix &, double);
  Matrix operator/(const Matrix &, double);

  bool operator==(const Matrix &, const Matrix &);
  bool operator!=(const Matrix &, const Matrix &);

  std::istream &operator>>(std::istream &, Matrix &);
  std::ostream &operator<<(std::ostream &, const Matrix &);

  Vector operator*(const Matrix &, const Vector &);
  Vector operator*(const Vector &, const Matrix &);
} // namespace mapra

#endif // MATRIX_H_
