#include <rt/textures/perlin.h>
#include <core/interpolate.h>
#include <cmath>

namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black)
{
    /* TODO */
    this->white = white;
    this->black = black;
}

rt::RGBColor PerlinTexture::getColor(const Point& coord) {
    /* TODO */
    float turbulence = 0;
    float n = 0;
    for (int i = 0; i < amplitudes.size(); i++) {
        Point fix = Point(coord * frequencies[i]);
        float xweight = fix.x - floor(fix.x);
        float yweight = fix.y - floor(fix.y);
        float zweight = fix.z - floor(fix.z);
        float px0y0z0 = noise(floor(fix.x), floor(fix.y), floor(fix.z));
        float px0y0z1 = noise(floor(fix.x), floor(fix.y), ceil(fix.z));
        float px0y1z0 = noise(floor(fix.x), ceil(fix.y), floor(fix.z));
        float px0y1z1 = noise(floor(fix.x), ceil(fix.y), ceil(fix.z));
        float px1y0z0 = noise(ceil(fix.x), floor(fix.y), floor(fix.z));
        float px1y0z1 = noise(ceil(fix.x), floor(fix.y), ceil(fix.z));
        float px1y1z0 = noise(ceil(fix.x), ceil(fix.y), floor(fix.z));
        float px1y1z1 = noise(ceil(fix.x), ceil(fix.y), ceil(fix.z));

        n = lerp3d(px0y0z0, px1y0z0, px0y1z0, px1y1z0, px0y0z1, px1y0z1, px0y1z1, px1y1z1, xweight, yweight, zweight);

        turbulence += amplitudes[i] * n;
    }
    return(lerp(black, white, (turbulence + 1) / 2));
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    return RGBColor::rep(0.0f);
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    return RGBColor::rep(0.0f);
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    /* TODO */
    amplitudes.push_back(amplitude);
    frequencies.push_back(frequency);
    amplitude_sum += amplitude;
}

}
