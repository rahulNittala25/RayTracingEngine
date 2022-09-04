#include <rt/solids/quadric.h>

namespace rt {

  Quadric::Quadric(float na, float nb, float nc, float nd, float ne,
        float nf, float ng, float nh, float ni, float nj, CoordMapper* texMapper, Material* material)
  : a(na), b(nb), c(nc)
  , d(nd), e(ne), f(nf)
  , g(ng), h(nh), i(ni)
  , j(nj), material(material)
  {
  }

  // Return the normal vector at point v of this surface
Vector Quadric::getNormal(const Point &p) const
  {
    Vector v = Vector(p.x,p.y,p.z);
    Vector temp(dot(v,Vector(2*a,b,c)) + d,
          dot(v,Vector(b,2*e,f)) + g,
          dot(v,Vector(c,f,2*j)) + i);
     return temp.normalize();
  }

  BBox Quadric::getBounds() const {
      /* TODO */ NOT_IMPLEMENTED;
  }

Intersection Quadric::intersect(const Ray& ray, float previousBestDistance) const {
  float t = -1.0, A, B, C, root, disc;

  A = dot(Vector(a,b,c), Vector(ray.d.x*ray.d.x,ray.d.y*ray.d.y,ray.d.z*ray.d.z)) + d*ray.d.x*ray.d.y + e*ray.d.x*ray.d.z + f*ray.d.y*ray.d.z;

  B = 2*(a*ray.o.x*ray.d.x + b*ray.o.y*ray.d.y + c*ray.o.z*ray.d.z)
     + d*(ray.o.x*ray.d.y + ray.o.y*ray.d.x) + e*(ray.o.x*ray.d.z + ray.o.z*ray.d.x)
     + f*(ray.o.y*ray.d.z + ray.o.z*ray.d.y) + dot(Vector(g,h,i),ray.d);

  C = dot(Vector(a,b,c), Vector(ray.o.x*ray.o.x,ray.o.y*ray.o.y,ray.o.z*ray.o.z))
     + d*ray.o.x*ray.o.y + e*ray.o.x*ray.o.z + f*ray.o.y*ray.o.z
     +dot(Vector(g,h,i), Vector(ray.o.x,ray.o.y,ray.o.z));

  if (A != 0.0) {
     disc = B * B - 4.0 * A * C;
     if (disc > -1e-6) {
        root = sqrt(disc);
        t = (-B - root) / (A+A);
        if (t < 0.0)
           t = ( -B + root ) / (A+A);
     }
  }

  if ((1e-6 * 10.0) > t)
      return Intersection::failure();

  return Intersection(t, ray, this, getNormal(ray.getPoint(t)), ray.getPoint(t));
}

Solid::Sample Quadric::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float Quadric::getArea() const {
    /* TODO */ NOT_IMPLEMENTED;
}

}
