#pragma once
#include "grid.h"

struct GridMapping {
  Grid& _grid;
  float _res, _res_inverse;
  inline const float& res() {return _res;}
  inline const float& resInverse() {return _res_inverse;}
  GridMapping(Grid& g, float res):
    _grid(g),
    _res(res),
    _res_inverse(1./res)
  {}

  //origin in the middle of the grid, each pixel is "res" meters in the world
  inline Vector2f grid2world(const Vector2i& src) const {
    Vector2i pg=src-Vector2i(_grid._rows/2, _grid._cols/2);
    return Vector2f(pg.x()*_res_inverse, pg.y()*_res_inverse);
  }
  inline Vector2i world2grid(const Vector2f& src) const {
    Vector2i grid_center(_grid._rows/2, _grid._cols/2);
    return Vector2i(src.x()*_res, src.y()*_res)+grid_center;
  }
};
