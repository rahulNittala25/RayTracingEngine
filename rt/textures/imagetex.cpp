#include <rt/textures/imagetex.h>
#include <math.h>

namespace rt {

ImageTexture::ImageTexture()
{
    /* TODO */
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i)
{
    /* TODO */
    this->texture_img.readPNG(filename);
    img_width = texture_img.width();
    img_height = texture_img.height();
    this->bht = bh;
    this->it = i;
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i)
{
    /* TODO */
    this->texture_img = image;
    img_width = texture_img.width();
    img_height = texture_img.height();
    this->bht = bh;
    this->it = i;
}

RGBColor ImageTexture::getColor(const Point& coord) {
    /* TODO */
    float tx, ty, tz;//fractional coordinates
    int lx, ly, lz;//lattice coordinates

    lx = floor(coord.x);
    ly = floor(coord.y);
    lz = floor(coord.z);

    tx = coord.x - floor(coord.x);
    ty = coord.y - floor(coord.y);
    tz = coord.z - floor(coord.z);

    if (bht == BorderHandlingType::MIRROR) {
        if (abs(lx) % 2 == 1) {
            tx = 1 - tx;
        }
        if (abs(ly) % 2 == 1) {
            ty = 1 - ty;
        }
        if (abs(lz) % 2 == 1) {
            tz = 1 - tz;
        }
    }
    if (bht == BorderHandlingType::CLAMP) {
        if (coord.x < 0) {
            tx = 0;
        }
        else if (coord.x > 1) {
            tx = 1;
        }
        if (coord.y < 0) {
            ty = 0;
        }
        else if (coord.y > 1) {
            ty = 1;
        }
        if (coord.z < 0) {
            tz = 0;
        }
        else if (coord.z > 1) {
            tz = 1;
        }
    }

    if (it == InterpolationType::NEAREST) {
        float u, v;
        u = tx * img_width;
        v = ty * img_height;
        int img_x, img_y;
        img_x = (floor(u) < (img_width - 1)) ? floor(u) : (img_width - 1);
        img_y = (floor(v) < (img_height - 1)) ? floor(v) : (img_height - 1);
        return texture_img(img_x, img_y);
    }
    if (it == InterpolationType::BILINEAR) {
        float u, v;
        u = tx * (img_width - 1);
        v = ty * (img_height - 1);
        float fu, fv;
        fu = u - floor(u);
        fv = v - floor(v);
        float u0 = floor(u), u1 = ceil(u), v0 = floor(v), v1 = ceil(v);
        return((1 - fu) * (1 - fv) * texture_img(u0, v0) + (1 - fu) * (fv)*texture_img(u0, v1) + (fu) * (1 - fv) * texture_img(u1, v0) + (fu) * (fv)*texture_img(u1, v1));
    }
    return(RGBColor::rep(0.0f));
}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    Point p1 = Point(coord.x + 0.5f / img_width, coord.y, coord.z);
    Point p2 = Point(coord.x - 0.5f / img_width, coord.y, coord.z);
    return getColor(p1) - getColor(p2);
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    Point p1 = Point(coord.x, coord.y + 0.5f / img_height, coord.z); //may improve depth by multiplying the y coord here
    Point p2 = Point(coord.x, coord.y - 0.5f / img_height, coord.z);
    return getColor(p1) - getColor(p2);
}

}
