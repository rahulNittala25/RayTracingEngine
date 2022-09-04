#include <rt/materials/lambertian.h>
#include <rt/textures/texture.h>

namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse)
{
    this->emission = emission;
    this->diffuse = diffuse;
}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return (diffuse->getColor(texPoint) * dot(normal, inDir) / pi);
}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return (emission->getColor(texPoint) * dot(normal, outDir));
}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    return(SampleReflectance());
}

Material::Sampling LambertianMaterial::useSampling() const {
	return SAMPLING_NOT_NEEDED;
}

}