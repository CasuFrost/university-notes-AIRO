#pragma once
#include <opencv4/opencv2/opencv.hpp>
#include "world_item.h"

struct LaserScanner;

struct LaserScan
{
  float *ranges;
  int ranges_num;
  float angle_min;
  float angle_max;
  float range_min;
  float range_max;
  LaserScan(int nranges,
            float amin,
            float amax,
            float rmin,
            float rmax);
  ~LaserScan();
  void draw(cv::Mat, const Isometry2f &lidar_pose, const GridMapping &mapping);
};

struct LaserScanner : public WorldItem
{
  LaserScan &_scan;
  float _range_max_in_pixels;
  float _range_min_in_pixels;

  LaserScanner(LaserScan &scan_,
               WorldItem &parent_,
               const Isometry2f pip);

  void timerTick(float dt) override;
};
