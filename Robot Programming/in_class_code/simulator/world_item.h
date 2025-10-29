#pragma once
#include <cassert>
#include "linalg.h"
#include "grid_mapping.h"
#include <cmath>

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

  WorldItem(WorldItem *parent, const Isometry2f pose_in_parent);
  WorldItem(GridMapping &mapping_);

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

struct LaserScanner;

struct LaserScan
{
  float *ranges;
  int num_ranges;
  float angle_min;
  float angle_max;
  float range_min;
  float range_max;
  LaserScan(int nranges,
            float amin,
            float amax,
            float rmin,
            float rmax) : num_ranges(nranges),
                          angle_min(amin),
                          angle_max(amax),
                          range_min(rmin),
                          range_max(rmax)
  {
    assert(nranges && "buy a real lidar");
    ranges = new float[num_ranges];
  }
  ~LaserScan()
  {
    delete[] ranges;
  }
};

struct LaserScanner : public WorldItem
{
  LaserScan &_scan;
  GridMapping &_mapping;
  float _range_max_in_pixels;
  float _range_min_in_pixels;

  LaserScanner(LaserScan &scan_,
               GridMapping &mapping_,
               WorldItem *parent_,
               const Isometry2f pip) : WorldItem(parent_, pip),
                                       _scan(scan_),
                                       _mapping(mapping_)
  {
    _range_max_in_pixels = _mapping._res * _scan.range_max;
    _range_min_in_pixels = _mapping._res * _scan.range_min;
  }

  void timerTick(float dt) override
  {
    Isometry2f wt = poseInWorld();
    Vector2i gp = _mapping.world2grid(wt._translation);
    float angle_increment = (_scan.angle_max - _scan.angle_min) / _scan.num_ranges;
    float angle_start = _scan.angle_min + wt._rotation.angle();
    float range_max_in_pixels = _mapping._res * _scan.range_max;
    float range_min_in_pixels = _mapping._res * _scan.range_min;
    Grid &grid = _mapping._grid;

    float alpha = angle_start;
    for (int i = 0; i < _scan.num_ranges; ++i)
    {
      Vector2f hit;
      bool ep_found = grid.scanRay(hit, Vector2f(gp.x(), gp.y()), alpha, range_min_in_pixels, range_max_in_pixels);
      float range = _scan.range_max;
      if (ep_found)
      {
        Vector2f ep_m = _mapping.grid2world(Vector2i(hit.x(), hit.y()));
        Vector2f delta = ep_m - wt._translation;
        float range = sqrt(delta.dot(delta));
        if (range < _scan.range_min)
          range = _scan.range_min;
      }
      _scan.ranges[i] = range;
    }
  }
};
