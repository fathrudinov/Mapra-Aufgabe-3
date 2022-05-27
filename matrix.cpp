#include "matrix.h"
using namespace mapra;

mapra::Matrix::Matrix(std::size_t r = 1, std::size_t c = 1)
{
}

double &Matrix::operator()(std::size_t, std::size_t)
{
}
double Matrix::operator()(std::size_t, std::size_t) const
{
}

Matrix &Matrix::operator+=(const Matrix &)
{
}
Matrix &Matrix::operator-=(const Matrix &)
{
}
Matrix &Matrix::operator*=(const Matrix &)
{
}
Matrix &Matrix::operator*=(double)
{
}
Matrix &Matrix::operator/=(double)
{
}

Matrix &Matrix::Redim(std::size_t, std::size_t)
{
}

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