#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity):light_position(position), light_intensity(intensity)
{
    /* TODO */
}

LightHit PointLight::getLightHit(const Point& p) const {
    /* TODO */
    LightHit hit;
    hit.direction = light_position - p;
    hit.distance = hit.direction.length();
    hit.direction = hit.direction.normalize();
    hit.normal = hit.direction;
    return(hit);
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    return(light_intensity / (irr.distance*irr.distance));
}

}
