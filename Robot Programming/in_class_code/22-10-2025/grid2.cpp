#include <cassert>
#include "opencv2/opencv.hpp"

#include "grid2.h"

Grid::Grid(int r, int c)
{
  if (!r || !c)
  {
    _rows = 0;
    _cols = 0;
    _values = 0;
    return;
  }
  _rows = r;
  _cols = c;
  _values = new CellType[r * c];
}

Grid::~Grid()
{
  if (!_values)
    return;
  delete[] _values;
}

Grid::Grid(const Grid &other) : Grid(other._rows, other._cols)
{
  int s = _rows * _cols;
  for (int i = 0; i < s; ++i)
    _values[i] = other._values[i];
}

void Grid::resize(int r, int c)
{
  int other_s = r * c;
  int s = _rows * _cols;
  if (other_s != s)
  {
    if (_values)
    {
      delete[] _values;
      _values = 0;
    }
    if (other_s)
      _values = new CellType[other_s];
  }
  _rows = r;
  _cols = c;
}

Grid &Grid::operator=(const Grid &other)
{
  if (&other == this)
    return *this;
  resize(other._rows, other._cols);
  int size = _rows * _cols;
  for (int i = 0; i < size; ++i)
    _values[i] = other._values[i];
  return *this;
}

void Grid::loadFromImage(const char *filename)
{
  std::cerr << "loading [" << filename << "]" << std::endl;
  cv::Mat img = cv::imread(filename);
  if (img.rows == 0)
  {
    throw std::runtime_error("unable to load image");
  }
  cv::Mat img_gray;
  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
  resize(img_gray.rows, img_gray.cols);
  _rows = img_gray.rows;
  _cols = img_gray.cols;
  memcpy(_values, img_gray.data, img_gray.rows * img_gray.cols);
}

cv::Mat Grid::toCvMat()
{
  cv::Mat m(_rows, _cols, CV_8UC1);
  memcpy(m.data, _values, _rows * _cols);
  return m;
}

bool Grid::scanRay(Vector2f &hit, const Vector2f &origin, float alpha, float max_range, uint8_t obstacle_value)
{
  if (!inside(origin.x(), origin.y()))
  {
    return false;
  }
  Vector2f dir(cos(alpha), sin(alpha));
  Vector2f p = origin;
  while (1)
  {
    if (!inside(p.x(), p.y()))
    {
      return false;
    }
    uint8_t val = at(p.x(), p.y());
    if (val < obstacle_value)
    {
      hit = p;
      return true;
    }
    p += dir;
  }
}
