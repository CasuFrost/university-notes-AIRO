#include <iostream>
#include "mat_d.h"
#include <assert.h>

MatD::MatD(int r, int c)
{
    if (!r || !c)
    {
        _rows = 0;
        _cols = 0;
        _values = nullptr;
        return;
    }
    _rows = r;
    _cols = c;
    _values = new double[r * c];
}

MatD::~MatD()
{
    if (_values != nullptr)
        delete[] _values;
}

MatD::MatD(const MatD &other) : MatD(other._rows, other._cols)
{
    int s = _rows * _cols;
    for (int i = 0; i < s; ++i)
        _values[i] = other._values[i];
}

MatD &MatD::operator=(const MatD &other)
{
    int other_s = other._cols * other._rows;
    int s = _rows * _cols;
    if (other_s != s)
    {
        if (_values)
        {
            delete[] _values;
            _values = nullptr;
        }
        _values = new double[other_s];
    }
    _rows = other._rows;
    _cols = other._cols;
    for (int i = 0; i < other_s; ++i)
        _values[i] = other._values[i];
    return *this;
}

MatD &MatD::operator+(const MatD &other) const
{
    assert(other._rows == _rows && _cols == other._cols && "errors on matrix size");
    MatD ret(*this);
    for (int r = 0; r < _rows; ++r)
    {
        for (int c = 0; c < _cols; ++c)
        {
            ret.at(r, c) += other.at(r, c);
        }
    }
    return ret;
}

MatD &MatD::operator-(const MatD &other) const
{
    assert(other._rows == _rows && _cols == other._cols && "errors on matrix size");
    MatD ret(*this);
    for (int r = 0; r < _rows; ++r)
    {
        for (int c = 0; c < _cols; ++c)
        {
            ret.at(r, c) -= other.at(r, c);
        }
    }
    return ret;
}

MatD MatD::operator*(double s) const
{
    MatD ret(*this);
    for (int r = 0; r < _rows; ++r)
        for (int c = 0; c < _cols; ++c)
            ret.at(r, c) = ret.at(r, c) * s;
}
VecD MatD::operator*(const VecD &v) const
{
    assert(v.size == _cols && "vector and matrix isn't compatible");
    VecD ret(_rows);
    for (int r = 0; r < _rows; ++r)
    {
        double &acc = ret.at(r);
        acc = 0;
        for (int c = 0; c < _cols; ++c)
        {
            acc += at(r, c) * v.at(c);
        }
        ret.at(r) = acc;
    }
    return ret;
}

MatD &MatD::operator*(const MatD &other) const
{
    assert(other._rows == _cols && "matrices  isn't compatible");
    MatD ret(_rows, other._cols);
    for (int r = 0; r < ret._rows; ++r)
    {
        for (int c = 0; c < ret._cols; ++c)
        {
            double acc = 0; // ret.at(r, c);
            for (int i = 0; i < _cols; ++i)
            {
                acc += at(r, i) * other.at(i, c);
            }
            ret.at(r, c) = acc;
        }
    }
    return ret;
}

double &MatD::at(int r, int c) const
{
    // std::cout << r << " " << c << "\n";
    assert(r >= 0 && r <= _rows && c >= 0 && c <= _cols && "errors on matrix size");
    return _values[r * _cols + c];
}

double &MatD::at(int r, int c)
{
    // std::cout << r << " " << c << "\n";
    assert(r >= 0 && r <= _rows && c >= 0 && c <= _cols && "errors on matrix size");
    return _values[r * _cols + c];
}

double *_values;
int _rows, _cols;

void MatD::printMeBadly(std::ostream &os) const
{
    os << "this: " << this << std::endl;
    os << "rows: " << _rows << std::endl;
    os << "cols: " << _cols << std::endl;
    os << "values: [ " << std::endl;
    for (int r = 0; r < _rows; ++r)
    {
        for (int c = 0; c < _cols; ++c)
        {
            os << " " << at(r, c);
        }
        os << std::endl;
    }

    os << "]" << std::endl;
}
