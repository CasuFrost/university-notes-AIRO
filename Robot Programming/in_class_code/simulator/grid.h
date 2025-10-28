#pragma once
#include <cstdint>
#include <cassert>
#include <opencv2/opencv.hpp>
#include "linalg.h"
using CellType=uint8_t;

struct Grid {
  Grid(int r=0, int c=0);
  ~Grid();
  Grid(const Grid& other);
  Grid& operator=(const Grid& other);
  void resize(int r, int c);
  inline CellType& at(int r, int c){
    assert(r>=0 && r<_rows && c>=0 && c<_cols && "out of bounds");
    return _values[r*_cols+c];
  }

  inline CellType& at(int r, int c) const {
    assert(r>=0 && r<_rows && c>=0 && c<_cols && "out of bounds");
    return _values[r*_cols+c];
  }

  inline Vector2i pos(const CellType& c) const {
    const CellType* c_ptr=&c;
    int offset=(c_ptr-_values);
    assert(offset>=0 && offset<_rows*_cols && "excruciating pain");
    return Vector2i(offset/_cols, offset%_cols);
  }

    
  inline bool inside(const Vector2i& p) const {
    return p.x()>=0 && p.x()<_rows
      && p.y()>=0 && p.y()<_cols;
  }
  inline bool inside(int r, int c) {
    return r>=0 && r<_rows
      && c>=0 && c<_cols;
  }

  
  void loadFromImage(const char* image_name);
  cv::Mat toCvMat() const;

  // for tomorrow
  bool scanRay(Vector2f& hit,
               const Vector2f& origin,
               float alpha,
               float range_min,
               float range_max,
               uint8_t obstacle_value = 127);

  CellType* _values;
  int _rows,  _cols;
};


  

/*
struct LaserScanner;

struct LaserScan{
  LaserScanner& _scanner;
  float* ranges;
  int num_ranges;
  float angle_min;
  float angle_max;
  float range_min;
  float range_max;
  LaserScan(int nranges, float amin, float amax, float nranges, float rmin, float rmax);
  ~LaserScan();
};

struct LaserScanner: public WorldItem {
  
};

struct UnicycleRobot: public WorldItem {
};
*/
