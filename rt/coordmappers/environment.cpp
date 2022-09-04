#include <rt/coordmappers/environment.h>
#include <rt/intersection.h>

namespace rt{

    Point EnvironmentMapper::getCoords(const rt::Intersection &hit) const {
        return Point(hit.ray.d.x, hit.ray.d.y, hit.ray.d.z);
    }
};
