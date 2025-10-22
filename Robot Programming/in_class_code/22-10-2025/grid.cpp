#include <cassert>
#include "grid.h"

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

Grid &Grid::operator=(const Grid &other)
{
  int other_s = other._rows * other._cols;
  int s = _rows * _cols;
  if (other_s != s)
  {
    if (_values)
    {
      delete[] _values;
      _values = 0;
    }
    _values = new CellType[other_s];
  }
  _rows = other._rows;
  _cols = other._cols;
  for (int i = 0; i < other_s; ++i)
    _values[i] = other._values[i];
  return *this;
}

void loadFromImage(const char *image_name)
{
  cv::Mat img = cv::loadImage(image_name);
  resize(img.rows, img.columns);
}
cv::Mat Grid::toCvMat() const {}
