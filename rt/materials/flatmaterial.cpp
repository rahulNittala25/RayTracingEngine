#include <rt/materials/flatmaterial.h>
#include <rt/textures/texture.h>

namespace rt {

FlatMaterial::FlatMaterial(Texture* texture)
{
    /* TODO */
    this->texture = texture;
}

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */
    return(RGBColor::rep(0.0f));
}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */
    return(texture->getColor(texPoint));
}

Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    UNREACHABLE;
}

Material::Sampling FlatMaterial::useSampling() const {
    /* TODO */
    return(Material::Sampling::SAMPLING_NOT_NEEDED);
}

}