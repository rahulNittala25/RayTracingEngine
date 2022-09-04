#include <core/assert.h>
#include <core/macros.h>
#include <rt/ray.h>

namespace rt {

Ray::Ray(const Point& o, const Vector& d, float t)
{
    assert(d != Vector::rep(0.0f));
    this->o = o;
    this->d = d;
		this->t = t;
}

Point Ray::getPoint(float distance) const {
  return o + (distance * d);
}

}
