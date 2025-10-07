#pragma once
using namespace std;
#include "vec_d.h"
#include "mat_d.h"
#include <cmath>

int main(int argc, char **argv)
{
    MatD m(3, 6);
    int s = m._rows * m._cols;
    for (int r = 0; r < m._rows; ++r)
    {
        for (int c = 0; c < m._cols; ++c)
        {
            m.at(r, c) = sin(M_PI / 100 * r) * cos(M_PI / 100 * c);
        }
    }

    m.printMeBadly(cout);

    return 0;
    VecD f;
    {
        VecD f2(5);
        for (int i = 0; i < f2.size; ++i)
        {
            f2.at(i) = sin(M_PI / 180 * i);
        }
        f = f2;
    }
    VecD f1(5);
    f.printMeBadly(cout);
    f1 = f - f;
    f1.printMeBadly(cout);
    cout << f * f1 << '\n';
    (f * 5 - f1).printMeBadly(cout);
    return 0;
}