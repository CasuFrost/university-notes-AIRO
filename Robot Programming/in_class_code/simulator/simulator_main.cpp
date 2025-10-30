#include <opencv2/opencv.hpp>
#include "linalg.h"
#include "grid2.h"


int main(int argc, char** argv) {
  if (argc<2)
    return -1;
  const char* filename=argv[1];
  Grid g;
  g.loadFromImage(filename);
  cv::Mat m=g.toCvMat();
  cv::imshow("grid", m);
  cv::waitKey(0);
}
