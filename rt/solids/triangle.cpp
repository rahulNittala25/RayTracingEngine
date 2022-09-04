#include <rt/solids/triangle.h>
#include <rt/coordmappers/world.h>
#include <core/random.h>
#include <core/float4.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
  this->v1 = vertices[0];
  this->v2 = vertices[1];
  this->v3 = vertices[2];
  this->normal = cross((v2 - v1), (v3 - v1)).normalize();
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
  this->v1 = v1;
  this->v2 = v2;
  this->v3 = v3;
  this->normal = cross((v2 - v1), (v3 - v1)).normalize();
}

BBox Triangle::getBounds() const {
  Point min = rt::min(rt::min(v1, v2), v3);
  Point max = rt::max(rt::max(v1, v2), v3);
	return BBox(min, max);
}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
  if (dot(ray.d, this->normal) == 0.0) return Intersection::failure();
  float t = - dot(ray.o - v1, normal) / dot(ray.d, this->normal);
	if (t > previousBestDistance || t < epsilon) return Intersection::failure();

  Vector e1 = v2 - v1;
  Vector e2 = v3 - v1;
  Vector pvec = cross(ray.d, e2);
  float det = dot(e1, pvec);

  if (fabs(det) < epsilon)
    return Intersection::failure();

  float invDet = 1.0 / det;
  Vector tvec = ray.o - v1;

  float u = dot(tvec, pvec) * invDet;

  if (u < 0 || u > 1)
    return Intersection::failure();

  Vector qvec = cross(tvec, e1);
  float v = dot(ray.d, qvec) * invDet;

  if (v < 0 || u + v > 1)
    return Intersection::failure();

  t = dot(e2, qvec) * invDet;
  return Intersection(t, ray, this, normal, Point(1-u-v, u, v));
}

Solid::Sample Triangle::sample() const {
    float u = random(), v = random(), w = random();
    u = u / (u + v + w);
    v = v / (u + v + w);
    w = 1 - u - v;
    Solid::Sample s{};
    s.point = Point(u * Float4(v1) + v * Float4(v2) + w * Float4(v3));
    s.normal = normal;
    return(s);
}

float Triangle::getArea() const {
  return cross(v2 - v1, v3 - v1).length() / 2;
}

}
