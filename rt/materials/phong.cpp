#include <rt/materials/phong.h>
#include <rt/textures/texture.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent)
{
    /* TODO */
    this->specular = specular;
    this->exponent = exponent;
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return(specular->getColor(texPoint) * pow(dot((-inDir + 2 * dot(inDir, normal) * normal).normalize(), outDir.normalize()), exponent)) * dot(inDir, normal) * (exponent + 2)/(2*pi);
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return(RGBColor::rep(0));
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return(SampleReflectance());
}

Material::Sampling PhongMaterial::useSampling() const {
    return SAMPLING_NOT_NEEDED;
}

}