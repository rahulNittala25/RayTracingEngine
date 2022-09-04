#include <core/point.h>
#include <core/float4.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Point::Point(const Float4& f4)
{
    //If |f4.w|< epsilon, it is a vector... not a point
    assert(fabs(f4.w) >= epsilon);
    this->x = f4.x/f4.w;
    this->y = f4.y/f4.w;
    this->z = f4.z/f4.w;
}

Vector Point::operator - (const Point& b) const {
  return Vector(x - b.x, y - b.y, z - b.z);
}

bool Point::operator == (const Point& b) const {
  // set bools for each float comparison with epsilon
  bool bool_x = (fabs(x - b.x) <= epsilon);
  bool bool_y = (fabs(y - b.y) <= epsilon);
  bool bool_z = (fabs(z - b.z) <= epsilon);

  if(bool_x && bool_y && bool_z)
    return true;
  else
    return false;
}

bool Point::operator != (const Point& b) const {
  return !((*this) == b);
}

Point operator * (float scalar, const Point& b) {
  return Point(scalar * b.x, scalar * b.y, scalar * b.z);
}

Point operator * (const Point& a, float scalar) {
  return Point(scalar * a.x, scalar * a.y, scalar * a.z);
}


Point min(const Point& a, const Point& b) {
  return Point(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point max(const Point& a, const Point& b) {
  return Point(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

float Point::getAxis(const int index) const {
    if (index == 0)
        return x;
    else if (index == 1)
        return y;
    else
        return z;
}

Point operator+(const Point& a, const Point& b)
{
    return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

}

