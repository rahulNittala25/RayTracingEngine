#include <rt/lights/arealight.h>
#include <rt/solids/solid.h>
#include <rt/materials/material.h>
#include <core/color.h>
#include <core/float4.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    LightHit hit;
    Solid::Sample s = source->sample();
    hit.direction = s.point - p;
    hit.distance = hit.direction.length();
    hit.distance = (1 - 0.0001f)*hit.direction.length();
    hit.direction = hit.direction.normalize();
    hit.normal = s.normal;
    return(hit);
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    /* TODO */
    RGBColor intensity = source->material->getEmission(Point::rep(0.0f), irr.normal, -irr.direction) * area;
    return intensity*std::abs(dot(irr.normal, irr.direction)) / pow(irr.distance, 2);
}

AreaLight::AreaLight(Solid* source)
{
    this->source = source;
    this->area = source->getArea();
}

}