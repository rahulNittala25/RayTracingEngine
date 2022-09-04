#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>

namespace rt {

Vector::Vector(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector::Vector(const Float4& f4)
{
    // Since f4.w is float, f4.w==0 ~ f4.w<epsilon
    assert(fabs(f4.w) <= epsilon);
    this->x = f4.x;
    this->y = f4.y;
    this->z = f4.z;
}

Vector Vector::operator + (const Vector& b) const {
  return Vector(x + b.x, y + b.y, z + b.z);
}

Vector Vector::operator - (const Vector& b) const {
  return Vector(x - b.x, y - b.y, z - b.z);
}

Vector Vector::operator - () const {
  Vector inv  = -1.0 * (*this);
  return inv;
}

Vector Vector::normalize() const {
  return (*this) / length();
}

Vector operator * (float scalar, const Vector& b) {
  return Vector(scalar * b.x, scalar * b.y, scalar * b.z);
}

Vector operator * (const Vector& a, float scalar) {
  return Vector(scalar * a.x, scalar * a.y, scalar * a.z);
}

Vector operator / (const Vector& a, float scalar) {
  //assert(scalar != 0.0);
  if(scalar == 0.0)
    scalar = 1.0 / epsilon;
  else
    scalar = 1.0 / scalar;
  return scalar * a;
}

Vector operator / (const Vector& a, const Vector& b) {
  float x_comp = 1.0 / b.x;
  float y_comp = 1.0 / b.y;
  float z_comp = 1.0 / b.z;
  assert(x_comp && y_comp && z_comp);
  return Vector((a.x * x_comp), (a.y * y_comp), (a.z * z_comp));
}

Vector cross(const Vector& a, const Vector& b) {
  return Vector((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}

float dot(const Vector& a, const Vector& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Vector::lensqr() const {
  return dot(*this, *this);
}

float Vector::length() const {
  return sqrt(lensqr());
}

bool Vector::operator == (const Vector& b) const {
  // set bools for each float comparison with epsilon
  bool bool_x = (fabs(x - b.x) <= epsilon);
  bool bool_y = (fabs(y - b.y) <= epsilon);
  bool bool_z = (fabs(z - b.z) <= epsilon);

  if(bool_x && bool_y && bool_z)
    return true;
  else
    return false;
}

bool Vector::operator != (const Vector& b) const {
  return !((*this) == b);
}

Vector min(const Vector& a, const Vector& b) {
  return Vector(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vector max(const Vector& a, const Vector& b) {
  return Vector(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Point operator + (const Point& a, const Vector& b) {
  return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator + (const Vector& a, const Point& b) {
  return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}

Point operator - (const Point& a, const Vector& b) {
  return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}

Point operator * (const Float4& scale, const Point& p) {
  return(Point(p.x * scale.x / scale.w, p.y * scale.y / scale.w, p.z * scale.z / scale.w));
}

}
