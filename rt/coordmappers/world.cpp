#include <rt/coordmappers/world.h>
#include <rt/intersection.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    /* TODO */
    Point hit_point = hit.hitPoint();
    return(Point(hit_point.x * scale.x, hit_point.y * scale.y, hit_point.z * scale.z));
}

WorldMapper::WorldMapper()
{
    /* TODO */
}

WorldMapper::WorldMapper(const Vector& scale)
{
    /* TODO */
    this->scale = scale;
}

}