#include <rt/materials/dummy.h>
#include <core/assert.h>

namespace rt {

DummyMaterial::DummyMaterial() {
    /* TODO */
}

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    float cos_theta_i = dot(normal, inDir);
    return(RGBColor::rep((this->fr * cos_theta_i)));
}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return(RGBColor(0, 0, 0));
}

Material::SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ NOT_IMPLEMENTED;
}

}