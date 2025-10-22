#include "linalg.h"
#include "grid.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char **argv)
{
    Vector2f unox(1, 0);
    Vector2f unoy(0, 1);
    Rotation2f roto(2);

    Isometry2f iso(1, 0, 2);
    cout << iso.inverse() * unoy << endl;
    return 0;
}