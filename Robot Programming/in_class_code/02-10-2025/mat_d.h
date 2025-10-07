#include <iostream>
#include "vec_d.h"
#include <assert.h>
struct MatD
{
    MatD(int r = 0, int c = 0)
    {
        if (!r || !c)
        {
            _rows = 0;
            _cols = 0;
            _values = nullptr;
        }
        _rows = r;
        _cols = c;
        _values = new double[r * c];
    }

    ~MatD()
    {
        if (_values != nullptr)
            delete[] _values;
    }

    MatD(const MatD &other) : MatD(other._rows, other._cols)
    {
        int s = _rows * _cols;
        for (int i = 0; i < s; ++i)
            _values[i] = other._values[i];
    }

    MatD &operator=(const MatD &other)
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
    }

    MatD &operator+(const MatD &other) const
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
    /*
    MatD &operator-(const MatD &other) const;
    MatD &operator*(double &s);
    VecD &operator*(const VecD &v) const;
    MatD &operator*(const MatD &other) const;
    // double at(int r, int c) const;
    */
    double &at(int r, int c)
    {
        assert(r >= 0 && r < _rows && c >= 0 && c <= _cols && "errors on matrix size");
        return _values[r * _cols + c];
    }
    double &at(int r, int c) const;

    double *_values;
    int _rows, _cols;

    void printMeBadly(std::ostream &os)
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
};