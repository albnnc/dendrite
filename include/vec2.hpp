#pragma once

#include <iostream>
#include <cmath>

namespace dendrite
{

class Vec2
{
public:
  double x, y;

  Vec2() : x(0), y(0) {}
  Vec2(double x, double y) : x(x), y(y) {}
  Vec2(const Vec2 &v) : x(v.x), y(v.y) {}

  Vec2 &operator=(const Vec2 &v)
  {
    x = v.x;
    y = v.y;
    return *this;
  }

  Vec2 operator+(const Vec2 &v) { return Vec2(x + v.x, y + v.y); }
  Vec2 operator-(const Vec2 &v) { return Vec2(x - v.x, y - v.y); }

  Vec2 &operator+=(const Vec2 &v)
  {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vec2 &operator-=(const Vec2 &v)
  {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  Vec2 operator+(double n) { return Vec2(x + n, y + n); }
  Vec2 operator-(double n) { return Vec2(x - n, y - n); }
  Vec2 operator*(double n) { return Vec2(x * n, y * n); }
  Vec2 operator/(double n) { return Vec2(x / n, y / n); }

  Vec2 &operator+=(double s)
  {
    x += s;
    y += s;
    return *this;
  }

  Vec2 &operator-=(double s)
  {
    x -= s;
    y -= s;
    return *this;
  }

  Vec2 &operator*=(double s)
  {
    x *= s;
    y *= s;
    return *this;
  }

  Vec2 &operator/=(double s)
  {
    x /= s;
    y /= s;
    return *this;
  }

  void set(double x, double y)
  {
    this->x = x;
    this->y = y;
  }

  Vec2 normalize()
  {
    if (length() == 0)
      return Vec2(*this);
    return *this / length();
  }

  double length() const
  {
    return std::sqrt(x * x + y * y);
  }

  friend std::ostream &operator<<(std::ostream &os, const Vec2 &v)
  {
    os << "{" << v.x << ", " << v.y << "}";
    return os;
  }
};

}; // namespace dendrite
