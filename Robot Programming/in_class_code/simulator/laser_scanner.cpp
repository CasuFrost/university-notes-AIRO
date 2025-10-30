#include "laser_scanner.h"

LaserScan::LaserScan(int nranges,
                     float amin,
                     float amax,
                     float rmin,
                     float rmax) : ranges_num(nranges),
                                   angle_min(amin),
                                   angle_max(amax),
                                   range_min(rmin),
                                   range_max(rmax)
{
  assert(nranges && "buy a real lidar");
  ranges = new float[ranges_num];
}

LaserScan::~LaserScan()
{
  delete[] ranges;
}

LaserScanner::LaserScanner(LaserScan &scan_,
                           WorldItem &parent_,
                           const Isometry2f pip) : WorldItem(parent_, pip),
                                                   _scan(scan_)
{
  _range_max_in_pixels = _mapping._res * _scan.range_max;
  _range_min_in_pixels = _mapping._res * _scan.range_min;
}

void LaserScanner::timerTick(float dt)
{
  Isometry2f wt = poseInWorld();
  Vector2i gp = _mapping.world2grid(wt._translation);
  float angle_increment = (_scan.angle_max - _scan.angle_min) / _scan.ranges_num;
  float angle_start = _scan.angle_min + wt._rotation.angle();
  float range_max_in_pixels = _mapping._res * _scan.range_max;
  float range_min_in_pixels = _mapping._res * _scan.range_min;
  Grid &grid = _mapping._grid;

  for (int i = 0; i < _scan.ranges_num; ++i)
  {
    Vector2f hit;
    bool ep_found = grid.scanRay(hit, Vector2f(gp.x(), gp.y()), angle_start + i * angle_increment, range_min_in_pixels, range_max_in_pixels);

    float range = _scan.range_max;
    if (ep_found)
    {
      Vector2f ep_m = _mapping.grid2world(Vector2i(hit.x(), hit.y()));
      Vector2f delta = ep_m - wt._translation;
      range = sqrt(delta.dot(delta));
      // if (range<_scan.range_min)
      // range= _scan.range_min;
    }
    // cerr << "scan_in_lasa " << &_scan << endl;
    _scan.ranges[i] = range;
    // cerr << "b" << ep_found << " " << hit << " range " << _scan.ranges[i] << " " << range << endl;
  }
}

void LaserScan::draw(cv::Mat canvas,
                     const Isometry2f &lidar_pose,
                     const GridMapping &mapping)
{
  Vector2i origin_px = mapping.world2grid(lidar_pose._translation);
  float angle_increment = (angle_max - angle_min) / ranges_num;
  float angle_start = angle_min + lidar_pose._rotation.angle();
  float range_max_in_pixels = mapping._res * range_max;
  float range_min_in_pixels = mapping._res * range_min;
  for (int i = 0; i < ranges_num; i++)
  {
    float r = ranges[i];
    if (r <= range_min || r >= range_max)
      continue;
    float alpha = angle_start + angle_increment * i;
    Vector2f dir(cos(alpha), sin(alpha));
    Vector2f ep_w = lidar_pose._translation + dir * r;
    Vector2i ep_px = mapping.world2grid(ep_w);
    cv::line(canvas,
             cv::Point(origin_px.y(), origin_px.x()),
             cv::Point(ep_px.y(), ep_px.x()),
             cv::Scalar(127), 1);
  }
}
