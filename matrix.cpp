#include "matrix.h"
#include <fstream>
#include <iomanip> // for std::setprecision()

using namespace mapra;

Matrix::Matrix(std::size_t r, std::size_t c)
    : rows_(r), cols_(c), elems_(r, std::vector<double>(c, 0)) {}

double &Matrix::operator()(std::size_t r, std::size_t c)
{
    return elems_.at(r).at(c);
}
double Matrix::operator()(std::size_t r, std::size_t c) const
{
    return elems_.at(r).at(c);
}

Matrix &Matrix::operator+=(const Matrix &x)
{
    if (x.rows_ != rows_ || x.cols_ != cols_)
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");

    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < cols_; j++)
            (*this)(i, j) += x(i, j);
    return *this;
}
Matrix &Matrix::operator-=(const Matrix &x)
{
    if (x.rows_ != rows_ || x.cols_ != cols_)
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");

    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < cols_; j++)
            (*this)(i, j) -= x(i, j);
    return *this;
}
Matrix &Matrix::operator*=(const Matrix &x)
{
    if (x.rows_ != cols_)
    {
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");
    }
    Matrix c = Matrix(rows_, x.cols_);

    for (int j = 0; j < x.cols_; j++)
        for (int i = 0; i < rows_; i++)
            for (int k = 0; k < rows_; k++)
                c(i, j) += (*this)(i, k) * x(k, j);
    *this = c;
    return (*this);
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

Matrix mapra::operator+(const Matrix &, const Matrix &);
Matrix mapra::operator-(const Matrix &, const Matrix &);
Matrix mapra::operator-(const Matrix &);

Matrix mapra::operator*(const Matrix &A, const Matrix &B)
{
    if (A.rows_ != B.cols_)
    {
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");
    }
    Matrix C = Matrix(A.rows_, B.cols_);

    for (int j = 0; j < B.cols_; j++)
        for (int i = 0; i < A.rows_; i++)
            for (int k = 0; k < A.rows_; k++)
                C(i, j) += A(i, k) * B(k, j);
    return C;
}
Matrix mapra::operator*(double, const Matrix &);
Matrix mapra::operator*(const Matrix &, double);
Matrix mapra::operator/(const Matrix &, double);

bool mapra::operator==(const Matrix &, const Matrix &);
bool mapra::operator!=(const Matrix &, const Matrix &);

std::ostream &mapra::operator<<(std::ostream &out, const Matrix &A)
{
    out << std::setprecision(4);
    for (int i = 0; i < A.rows_; i++)
    {
        for (int j = 0; j < A.cols_; j++)
            out << A(i, j) << '\t';
        out << std::endl;
    }
    return out;
}

std::istream &mapra::operator>>(std::istream &in, Matrix &A)
{
    for (int i = 0; i < A.rows_; i++)
        for (int j = 0; j < A.cols_; j++)
            in >> A(i, j);
}

Vector mapra::operator*(const Matrix &, const Vector &);
Vector mapra::operator*(const Vector &, const Matrix &);

void Matrix::MatError(const char str[])
{
    std::cerr << "\nVektorfehler: " << str << '\n'
              << std::endl;
    exit(1);
}