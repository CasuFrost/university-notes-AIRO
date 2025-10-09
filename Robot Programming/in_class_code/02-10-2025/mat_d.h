#include <iostream>
#include "vec_d.h"
#include <assert.h>
struct MatD
{
    MatD(int r = 0, int c = 0);
    ~MatD();
    MatD(const MatD &other);
    MatD &operator=(const MatD &other);
    MatD &operator+(const MatD &other) const;
    MatD &operator-(const MatD &other) const;
    MatD operator*(double s) const;
    VecD operator*(const VecD &v) const;
    MatD operator*(const MatD &other) const;
    double &at(int r, int c);
    double &at(int r, int c) const;
    void printMeBadly(std::ostream &os) const;

    double *_values;
    int _rows, _cols;
};