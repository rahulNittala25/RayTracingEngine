#include <rt/integrators/castingdist.h>
#include <rt/world.h>
#include <math.h>
namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    this->nearColor = nearColor;
    this->nearDist = nearDist;
    this->farColor = farColor;
    this->farDist = farDist;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
  Intersection intersection = world->scene->intersect(ray);

  if(intersection) {
    RGBColor color;
    if(intersection.distance < nearDist)
      color = nearColor;
    else if(intersection.distance > farDist)
      color = farColor;
    else
      color = nearColor + ((intersection.distance - nearDist) * (farColor - nearColor) / (farDist - nearDist));

    float value = dot(-ray.d.normalize(), intersection.normal().normalize());
    RGBColor grayValue = RGBColor::rep(value);

    return color * grayValue.clamp();
  }
  return RGBColor(0,0,0);
}

}
