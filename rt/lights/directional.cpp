#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color)
{
    this->light_dir = direction.normalize();
    this->light_color = color;
    /* TODO */
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    /* TODO */
    LightHit hit;
    hit.direction = -light_dir;
    hit.distance = FLT_MAX;
    hit.normal = -light_dir;
    return hit;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    return(light_color);
}

}
