#include <opencv2/opencv.hpp>
#include "linalg.h"
#include "grid2.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
  if (argc < 2)
    return -1;
  const char *filename = argv[1];
  Grid g;
  g.loadFromImage(filename);
  cv::Mat m = g.toCvMat();

  Vector2f origin(g._rows / 2, g._cols / 2);
  float alpha = 0;
  float alpha_inc = M_PI / 180;
  cv::Mat canvas = g.toCvMat();
  while (1)
  {
    Vector2f hit;
    cv::imshow("grid", m);
    if (!g.scanRay(hit, origin, alpha, 1000, uint8_t(127)))
    {
      continue;
      cout << "miss\n";
    }
    cv::line(canvas, cv::Point(origin.y(), origin.x()), cv::Point(hit.y(), hit.x()), cv::Scalar(127), 1);
    cv::waitKey(0);
    alpha += alpha_inc;
  }
}
