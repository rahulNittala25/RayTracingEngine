#include <rt/coordmappers/tmapper.h>
#include <rt/intersection.h>

namespace rt {

TriangleMapper::TriangleMapper(Point ntv[3])
{
    /* TODO */
    this->ntv[0] = Float4(ntv[0]);
    this->ntv[1] = Float4(ntv[1]);
    this->ntv[2] = Float4(ntv[2]);
}

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2)
{
    /* TODO */
    this->ntv[0] = Float4(tv0);
    this->ntv[1] = Float4(tv1);
    this->ntv[2] = Float4(tv2);
}

Point TriangleMapper::getCoords(const Intersection& hit) const {
    /* TODO */
    Point local = hit.local();
    Float4 texPoint = local.x * ntv[0] + local.y * ntv[1] + local.z * ntv[2];
    return(Point(texPoint));

}

}