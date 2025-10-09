using namespace std;
#include "mat_d.h"
#include <cmath>

int main()
{
    int rows = 3;
    int cols = 3;
    MatD m(rows, cols);
    MatD m2(cols, rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            m.at(i, j) = sin(i * j);
            m2.at(j, i) = cos(i * j);
        }
    }
    m.printMeBadly(cout);
    m2.printMeBadly(cout);
    MatD m3 = m * m2;
    m3.printMeBadly(cout);
}