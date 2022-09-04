#include <rt/solids/environmentsolid.h>
#include <rt/coordmappers/world.h>
#include <core/float4.h>

namespace rt{

EnvironmentSolid::EnvironmentSolid(CoordMapper *texMapper, Material *material) {
    if (texMapper == nullptr) {
      this->texMapper = new WorldMapper(Vector::rep(1.0f));
    } else {
      this->texMapper = texMapper;
    }
    this->material = material;
}

Intersection EnvironmentSolid::intersect(const rt::Ray &ray, float previousBestDistance) const {
    return Intersection(FLT_MAX/10, ray, this, ray.d, Point::rep(0.0f));
}

BBox EnvironmentSolid::getBounds() const {
    return BBox::full();
}

float EnvironmentSolid::getArea() const {
    return FLT_MAX;
}

Solid::Sample EnvironmentSolid::sample() const {
    NOT_IMPLEMENTED;
}

};
