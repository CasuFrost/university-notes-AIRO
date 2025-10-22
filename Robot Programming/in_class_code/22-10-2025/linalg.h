#pragma once
#include "math.h"
using namespace std;
#include <iostream>

struct Vector2f
{
  float _values[2];
  Vector2f(float x = 0, float y = 0)
  {
    _values[0] = x;
    _values[1] = y;
  }

  inline float x() const
  {
    return _values[0];
  }

  inline float y() const
  {
    return _values[1];
  }

  inline float &x()
  {
    return _values[0];
  }

  inline float &y()
  {
    return _values[1];
  }

  inline Vector2f operator+(const Vector2f &other) const
  {
    return Vector2f(_values[0] + other._values[0],
                    _values[1] + other._values[1]);
  }

  inline Vector2f operator-(const Vector2f &other) const
  {
    return Vector2f(_values[0] - other._values[0],
                    _values[1] - other._values[1]);
  }

  inline Vector2f &operator+=(const Vector2f &other)
  {
    _values[0] += other._values[0];
    _values[1] += other._values[1];
    return *this;
  }

  inline Vector2f &operator-=(const Vector2f &other)
  {
    _values[0] -= other._values[0];
    _values[1] -= other._values[1];
    return *this;
  }
};

struct Vector2i
{
  int _values[2];
  Vector2i(int x = 0, int y = 0)
  {
    _values[0] = x;
    _values[1] = y;
  }

  inline int x() const
  {
    return _values[0];
  }

  inline int y() const
  {
    return _values[1];
  }

  inline int &x()
  {
    return _values[0];
  }

  inline int &y()
  {
    return _values[1];
  }

  inline Vector2i operator+(const Vector2i &other) const
  {
    return Vector2i(_values[0] + other._values[0],
                    _values[1] + other._values[1]);
  }

  inline Vector2i operator-(const Vector2i &other) const
  {
    return Vector2i(_values[0] - other._values[0],
                    _values[1] - other._values[1]);
  }

  inline Vector2i &operator+=(Vector2i &other)
  {
    _values[0] += other._values[0];
    _values[1] += other._values[1];
    return *this;
  }

  inline Vector2i &operator-=(Vector2i &other)
  {
    _values[0] -= other._values[0];
    _values[1] -= other._values[1];
    return *this;
  }
};

struct Rotation2f
{
  float _values[2][2];

  Rotation2f()
  {
    _values[0][0] = 1;
    _values[0][1] = 0;
    _values[1][0] = 0;
    _values[1][1] = 1;
  }

  Rotation2f(float theta)
  {
    float s = sin(theta);
    float c = cos(theta);
    _values[0][0] = c;
    _values[0][1] = -s;
    _values[1][0] = s;
    _values[1][1] = c;
  }

  inline float angle() const
  {
    return atan2(_values[1][0], _values[0][0]);
  }

  inline Rotation2f operator*(const Rotation2f &other) const
  {
    Rotation2f ret;
    for (int r = 0; r < 2; ++r)
    {
      for (int c = 0; c < 2; ++c)
      {
        float acc = 0;
        for (int i = 0; i < 2; ++i)
        {
          acc += _values[r][i] * other._values[i][c];
        }
        ret._values[r][c] = acc;
      }
    }
    return ret;
  }

  inline Rotation2f transpose() const
  {
    Rotation2f ret(*this);
    ret._values[1][0] = -ret._values[1][0];
    ret._values[0][1] = -ret._values[0][1];
    return ret;
  }

  inline Vector2f operator*(const Vector2f &other) const
  {
    return Vector2f(_values[0][0] * other.x() + _values[0][1] * other.y(),
                    _values[1][0] * other.x() + _values[1][1] * other.y());
  }
};

struct Isometry2f
{
  Vector2f _translation;
  Rotation2f _rotation;

  // init to identity
  Isometry2f() : _translation(0, 0)
  {
  }

  // use your imagination
  Isometry2f(float x, float y, float theta) : _rotation(theta),
                                              _translation(x, y)
  {
  }

  // have fun
  void setIdentity()
  {
    _rotation = Rotation2f();
    _translation = Vector2f(0, 0);
  }

  // complete R*other.R | t+R*other.t
  Isometry2f operator*(const Isometry2f &other) const
  {
    Isometry2f ret;
    ret._rotation = _rotation * other._rotation;
    ret._translation = _rotation * other._translation + _translation;
    return ret;
  }

  Vector2f operator*(const Vector2f &other) const
  {
    // complete R*other+t
    return _rotation * other + _translation;
  }

  Isometry2f inverse() const
  {
    // complete R' | -R' *t
    Isometry2f ret;
    ret.setIdentity();
    ret._rotation = _rotation.transpose();
    ret._translation -= ret._rotation * _translation;
    return ret;
  }
};

ostream &operator<<(ostream &os, const Vector2f &v)
{
  os << "Vector2f: (" << v.x() << "  " << v.y() << ")";
  return os;
}

ostream &operator<<(ostream &os, const Rotation2f &rot)
{
  os << "Rotation2f: [[" << rot._values[0][0] << "  " << rot._values[0][1] << "],[" << rot._values[1][0] << "  " << rot._values[1][1] << "]]";
  return os;
}

ostream &operator<<(ostream &os, const Isometry2f &iso)
{
  os << "Isometry2f:\n"
     << iso._rotation << "\n"
     << iso._translation;
  return os;
}