#pragma once
#include <iostream>

struct VecD
{
    int size;
    double *values;

    VecD();

    VecD(const VecD &other);

    VecD(int size);

    ~VecD();

    double &at(int pos) const;

    void printMeBadly(std::ostream &os);

    // override operator
    VecD &operator=(const VecD &other);

    VecD operator+(const VecD &other) const;

    VecD operator-(const VecD &other) const;

    VecD operator*(const float s);

    double operator*(const VecD &other);
};