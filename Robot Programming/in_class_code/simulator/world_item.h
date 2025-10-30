#pragma once
#include <cassert>
#include "linalg.h"
#include "grid_mapping.h"
#include <cmath>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/core/base.hpp>

struct WorldItem;

struct WorldItemPtrVector
{
  WorldItem **_items = 0;
  int num_items = 0;
  inline WorldItem *at(int pos)
  {
    assert(pos >= 0 && pos < num_items && "male male male");
    return _items[pos];
  }

  void pushBack(WorldItem *new_item);

  ~WorldItemPtrVector();
};

struct WorldItem
{
  WorldItemPtrVector _children;
  Isometry2f _pose_in_parent;
  WorldItem *_parent;
  GridMapping &_mapping;

  WorldItem(WorldItem &parent, const Isometry2f &pose_in_parent);
  WorldItem(GridMapping &mapping_);

  virtual WorldItem *isColliding();

  virtual void timerTick(float dt);
  virtual void draw(cv::Mat canvas, GridMapping &mapping);
  ~WorldItem();

  inline Isometry2f poseInWorld();
};

Isometry2f WorldItem::poseInWorld()
{
  Isometry2f aux_iso(0, 0, 0);
  WorldItem *aux = this;
  while (aux)
  {
    aux_iso = aux->_pose_in_parent * aux_iso;
    aux = aux->_parent;
  }
  return aux_iso;
}
