#include <rt/solids/aabox.h>
#include <core/point.h>
#include <rt/coordmappers/world.h>

namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material): Solid(texMapper, material)
{
  this->minCorner = min(corner1, corner2);
  this->maxCorner = max(corner1, corner2);
}

BBox AABox::getBounds() const {
  return BBox(minCorner, maxCorner);
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
  float x = std::abs(maxCorner.x - minCorner.x);
  float y = std::abs(maxCorner.y - minCorner.y);
  float z = std::abs(maxCorner.z - minCorner.z);
  return 2 * (x*y + y*z + z*x) ;
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
  Vector near = (minCorner - ray.o) / ray.d;
  Vector far = (maxCorner - ray.o) / ray.d;

  float t_min = max(max(min(near.x, far.x),min(near.y, far.y)),min(near.z, far.z));
  float t_max = min(min(max(near.x, far.x),max(near.y, far.y)),max(near.z, far.z));

  if (t_max < 0 || t_min > t_max || t_max > FLT_MAX)
    return Intersection::failure();
  if (t_min > previousBestDistance || t_min < 0)
    return Intersection::failure();

  Vector n;
  n = t_min == near.x ? Vector(-1, 0, 0) : n;
  n = t_min == far.x ? Vector(1, 0, 0) : n;
  n = t_min == near.y ? Vector(0, -1, 0) : n;
  n = t_min == far.y ? Vector(0, 1, 0) : n;
  n = t_min == near.z ? Vector(0, 0, -1) : n;
  n = t_min == far.z ? Vector(0, 0, 1) : n;

  return Intersection(t_min, ray, this, n, ray.getPoint(t_min));
}

}
