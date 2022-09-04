#ifndef CG1RAYTRACER_SOLIDS_CYLINDER_HEADER
#define CG1RAYTRACER_SOLIDS_CYLINDER_HEADER

#include <rt/solids/solid.h>

namespace rt {

    class Cylinder : public Solid {
    public:
        Cylinder() {}
        Cylinder(float radius1, float radius2, float limit1, float limit2, CoordMapper* texMapper, Material* material);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;
    private:
        float radius1, radius2;
        float limit1, limit2;
    };

}


#endif
