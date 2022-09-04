#ifndef CG1RAYTRACER_PRIMMOD_BMAP_HEADER
#define CG1RAYTRACER_PRIMMOD_BMAP_HEADER

#include <rt/primitive.h>
#include <rt/coordmappers/tmapper.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>

namespace rt {

class Triangle;
class Texture;

class BumpMapper : public Primitive {
public:
    BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale);
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
    virtual float getArea() const { return 0; }
private:
    Triangle* base;
    Texture* bm;
    Point bv1;
    Point bv2;
    Point bv3;
    float vs;
};

}

#endif
