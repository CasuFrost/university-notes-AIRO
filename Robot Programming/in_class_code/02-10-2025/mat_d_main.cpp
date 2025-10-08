using namespace std;
#include "mat_d.h"
#include <cmath>

int main()
{
    MatD m(3, 6);
    MatD m2(6, 3);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            m.at(i, j) = 0.5;
            m2.at(j, i) = 2;
        }
    }
    m.printMeBadly(cout);
    m2.printMeBadly(cout);
    MatD m3 = m * m2;
}