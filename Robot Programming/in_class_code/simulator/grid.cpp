#include <cassert>
#include "grid.h"

Grid::Grid(int r, int c) {
  if (!r || !c) {
    _rows=0;
    _cols=0;
    _values=0;
    return;
  }
  _rows=r;
  _cols=c;
  _values=new CellType[r*c];
}

Grid::~Grid() {
  if (!_values)
    return;
  delete [] _values;
}
  
Grid::Grid(const Grid& other):
  Grid(other._rows, other._cols)
{
  int s=_rows*_cols;
  for (int i=0; i<s; ++i)
    _values[i]=other._values[i];
}
  
Grid& Grid::operator=(const Grid& other) {
  resize(other._rows, other._cols);
  memcpy(_values, other._values, _rows*_cols);
  return *this;
}

void Grid::resize(int r, int c) {
  int other_s=r*c;
  int s=_rows*_cols;
  if (other_s!=s) {
    if (_values) {
      delete [] _values;
      _values=0;
    }
    if (other_s)
    _values=new CellType[other_s];
  }
  _rows=r;
  _cols=c;
}


void Grid::loadFromImage(const char* image_name) {
  cv::Mat img=cv::imread(image_name);
  resize(img.rows, img.cols);
  cv::Mat img_gray;
  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
  memcpy(_values, img_gray.data, img.rows*img.cols);
  /*
  for (int i =0; i< img.rows*img.cols; ++i) {
    _values[i]=img.data[i];
  }
  */
}

cv::Mat Grid::toCvMat() const {
  cv::Mat img(_rows, _cols, CV_8UC1);
  memcpy(img.data, _values, _rows*_cols);
  return img;
}

bool Grid::scanRay(Vector2f& hit,
                   const Vector2f& origin,
                   float alpha,
                   float range_min,
                   float range_max,
                   uint8_t obstacle_value) {
  if (! inside(origin.x(), origin.y())) {
    return false;
  }
  Vector2f dir(cos(alpha), sin(alpha));
  Vector2f p=origin+dir*range_min;
  float l=range_min;
  while (l<range_max) {
    if (! inside(p.x(), p.y()))
      return false;
    uint8_t val=at(p.x(), p.y());
    if (val<obstacle_value) {
      hit=p;
      return true;
    }
    l+=1;
    p+=dir;
  }
  return false;
}
