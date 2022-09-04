#include <rt/integrators/casting.h>
#include <rt/intersection.h>
#include <rt/world.h>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
  Intersection intersection = world->scene->intersect(ray);
  if(intersection) {
    float value = -1.0f * dot(ray.d.normalize(), intersection.normal());
    return RGBColor::rep(value).clamp();
  }
  return RGBColor(0,0,0);
}

}
