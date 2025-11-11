#pragma once
#include <opencv2/opencv.hpp>
#include "world_item.h"

struct UnicycleRobot: public WorldItem {
  float radius_w;
  int radius_px;

  float velocity_translational = 0;
  float velocity_rotational = 0;
  
  UnicycleRobot(WorldItem& parent_,
                const Isometry2f pip,
                float radius);
  
  WorldItem* isColliding() override;

  void timerTick(float dt) override;
  
  void draw(cv::Mat canvas);



};
