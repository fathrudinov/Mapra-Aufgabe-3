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

    for (size_t j = 0; j < x.cols_; j++)
        for (size_t i = 0; i < rows_; i++)
            for (size_t k = 0; k < rows_; k++)
                c(i, j) += (*this)(i, k) * x(k, j);
    *this = c;
    return (*this);
}

Matrix &Matrix::operator*=(double x)
{
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < cols_; j++)
            (*this)(i, j) *= x;
    return *this;
}
Matrix &Matrix::operator/=(double x)
{
    if (x == 0)
    {
        Matrix::MatError("Division durch 0 nicht definiert!");
    }
    for (size_t i = 0; i < rows_; i++)
        for (size_t j = 0; j < cols_; j++)
            (*this)(i, j) /= x;
    return *this;
}

Matrix &mapra::Matrix::Redim(std::size_t r, std::size_t c)
{
    rows_ = r;
    cols_ = c;
    elems_.clear();
    elems_.resize(r, std::vector<double>(c, 0));
    return *this;
}

Matrix mapra::operator+(const mapra::Matrix &x, const mapra::Matrix &y)
{
    if (x.rows_ != y.rows_ || x.cols_ != y.cols_)
    {
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");
    }
    mapra::Matrix z = x;
    return z += y;
}

Matrix mapra::operator-(const mapra::Matrix &x, const mapra::Matrix &y)
{
    if (x.rows_ != y.rows_ || x.cols_ != y.cols_)
    {
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");
    }
    mapra::Matrix z = x;
    return z -= y;
}

Matrix mapra::operator-(const mapra::Matrix &x)
{
    mapra::Matrix z = x;
    return z *= (-1);
}

Matrix mapra::operator*(const Matrix &A, const Matrix &B)
{
    if (A.rows_ != B.cols_)
    {
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");
    }
    Matrix C = Matrix(A.rows_, B.cols_);

    for (size_t j = 0; j < B.cols_; j++)
        for (size_t i = 0; i < A.rows_; i++)
            for (size_t k = 0; k < A.rows_; k++)
                C(i, j) += A(i, k) * B(k, j);
    return C;
}

Matrix mapra::operator*(const mapra::Matrix &x, double y)
{
    mapra::Matrix z = x;
    return z *= y;
}

Matrix mapra::operator*(double y, const mapra::Matrix &x)
{
    mapra::Matrix z = x;
    return z *= y;
}

Matrix mapra::operator/(const mapra::Matrix &x, double y)
{
    mapra::Matrix z = x;
    return z /= y;
}

bool mapra::operator==(const mapra::Matrix &x, const mapra::Matrix &y)
{

    if (x.rows_ != y.rows_ || x.cols_ != y.cols_)
    {
        return false;
    }
    for (size_t i = 0; i < x.rows_; i++)
        for (size_t j = 0; j < x.cols_; j++)
            if (x(i, j) != y(i, j))
                return false;
    return true;
}

bool mapra::operator!=(const mapra::Matrix &x, const mapra::Matrix &y)
{
    if (x == y)
        return false;
    else
        return true;
}

std::ostream &mapra::operator<<(std::ostream &out, const Matrix &A)
{
    out << std::endl
        << std::setprecision(4);
    for (size_t i = 0; i < A.rows_; i++)
    {
        for (size_t j = 0; j < A.cols_; j++)
            out << A(i, j) << '\t';
        out << std::endl;
    }
    return out;
}

std::istream &mapra::operator>>(std::istream &in, Matrix &A)
{
    for (size_t i = 0; i < A.rows_; i++)
        for (size_t j = 0; j < A.cols_; j++)
            in >> A(i, j);
    return in;
}

std::size_t Matrix::GetRows() const
{
    return this->rows_;
}
std::size_t Matrix::GetCols() const
{
    return this->cols_;
}

Vector mapra::operator*(const mapra::Matrix &x, const mapra::Vector &y)
{
    if (x.GetCols() != y.GetLength())
    {
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");
    }
    mapra::Vector temp(x.GetRows());
    for (size_t row = 0; row < x.GetRows(); row++)
    {
        double z = 0;
        for (size_t j = 0; j < y.GetLength(); j++)
        {
            z = z + x(row, j) * y(j);
        }
        temp(row) = z;
    }
    return temp;
}

Vector mapra::operator*(const mapra::Vector &y, const mapra::Matrix &x)
{
    if (x.GetRows() != y.GetLength())
    {
        mapra::Matrix::MatError("Dimensionen sind ungueltig!");
    }
    mapra::Vector temp(x.GetCols());
    for (size_t col = 0; col < x.GetCols(); col++)
    {
        double z = 0;
        for (size_t j = 0; j < y.GetLength(); j++)
        {
            z = z + y(j) * x(j, col);
        }
        temp(col) = z;
    }
    return temp;
}

void Matrix::MatError(const char str[])
{
    std::cerr << "\nVektorfehler: " << str << '\n'
              << std::endl;
    exit(1);
}