#ifndef CG1RAYTRACER_SOLIDS_QUADRIC_HEADER
#define CG1RAYTRACER_SOLIDS_QUADRIC_HEADER

#include <rt/solids/solid.h>

namespace rt {

class Quadric : public Solid {
public:
    Quadric():a(0),b(0),c(0),d(0),e(0),f(0),g(0),h(0),i(0),j(0) {}
    Quadric(float na, float nb, float nc, float nd, float ne,
          float nf, float ng, float nh, float ni, float nj, CoordMapper* texMapper, Material* material);
    virtual BBox getBounds() const;
    virtual Vector getNormal(const Point& p) const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
    virtual Sample sample() const;
    virtual float getArea() const;
private:
  	float a,b,c,d,e,f,g,h,i,j;
    Material* material;
};

}

#endif
