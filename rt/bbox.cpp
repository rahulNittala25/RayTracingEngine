#include <rt/bbox.h>
#include <rt/solids/aabox.h>


namespace rt {

    BBox BBox::empty() {
        BBox bbox;
        bbox.isEmpty = true;
        return bbox;
    }

    BBox BBox::full() {
        Point minimum = Point(FLT_MIN, FLT_MIN, FLT_MIN);
        Point maximum = Point(FLT_MAX, FLT_MAX, FLT_MAX);
        return BBox(minimum, maximum);
    }


    void BBox::extend(const Point& point) {
        if (isEmpty) {
            isEmpty = false;
            min = point;
            max = point;
            return;
        }
        min = rt::min(this->min, point);
        max = rt::max(this->max, point);
        return;
    }

    void BBox::extend(const BBox& bbox) {
        if (isEmpty) {
            isEmpty = bbox.isEmpty;
            min = bbox.min;
            max = bbox.max;
            return;
        }
        min = rt::min(this->min, bbox.min);
        max = rt::max(this->max, bbox.max);
        return;
    }

    std::pair<float, float> BBox::intersect(const Ray& ray) const {
        Vector near = (min - ray.o) / ray.d;
        Vector far = (max - ray.o) / ray.d;

        float t_min = rt::max(rt::max(rt::min(near.x, far.x), rt::min(near.y, far.y)), rt::min(near.z, far.z));
        float t_max = rt::min(rt::min(rt::max(near.x, far.x), rt::max(near.y, far.y)), rt::max(near.z, far.z));

        return std::make_pair(t_min, t_max);
    }

    bool BBox::isUnbound() const {
        Point minimum = rt::min(min, max);
        Point maximum = rt::max(min, max);
        return (minimum.x == -FLT_MAX || minimum.y == -FLT_MAX || minimum.z == -FLT_MAX ||
            maximum.x == FLT_MAX || maximum.y == FLT_MAX || maximum.z == FLT_MAX);
    }


    Point BBox::centroid() const {
        Point centroid;
        centroid.x = (min.x + max.x) / 2;
        centroid.y = (min.y + max.y) / 2;
        centroid.z = (min.z + max.z) / 2;
        return centroid;
    }

    int BBox::largestAxis() const {
        // return the index and the length of the largest axis, 0:x,1:y, 2:z
        float lenx = max.x - min.x;
        float leny = max.y - min.y;
        float lenz = max.z - min.z;

        float length = std::max(std::max(lenx, leny), lenz);
        int axisIndex = (fabs(length - lenx) <= epsilon) ? 0 : 2;
        axisIndex = (fabs(length - leny) <= epsilon) ? 1 : axisIndex;

        return axisIndex;
    }
}