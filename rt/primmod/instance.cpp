#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    this->archetype = content;
    transform = Matrix::identity();
    inverse = transform;
}

Primitive* Instance::content() {
    return archetype;
}

void Instance::reset() {
    transform = Matrix::identity();
    inverse = transform;
}

void Instance::translate(const Vector& t) {
    Matrix translate = Matrix::identity();
    translate[0][3] = t.x;
    translate[1][3] = t.y;
    translate[2][3] = t.z;
    // concat the operation to total transformation
    concatTransform(translate);
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    Vector s;
    if (nnaxis.x < nnaxis.y && nnaxis.x < nnaxis.z) {
        s = Vector(0, -nnaxis.z, nnaxis.y).normalize();
    }
    else if (nnaxis.y < nnaxis.x && nnaxis.y < nnaxis.z) {
        s = Vector(-nnaxis.z, 0, nnaxis.x).normalize();
    }
    else {
        s = Vector(-nnaxis.y, nnaxis.x, 0).normalize();
    }
    Vector t = cross(nnaxis, s).normalize();
    //Matrix M_T = Matrix(Float4(nnaxis), Float4(s), Float4(t), Float4(0, 0, 0, 1));
    Matrix M = Matrix::system(nnaxis.normalize(), s, t);
    Matrix rotate = Matrix::identity();
    rotate[1][1] = cos(angle);
    rotate[1][2] = -sin(angle);
    rotate[2][1] = sin(angle);
    rotate[2][2] = cos(angle);
    // concat the operation to total transformation
    Matrix total = product(product(M, rotate), M.transpose());
    concatTransform(total);
}

void Instance::scale(float f) {
    this->scale(Vector(f, f, f));
}

void Instance::scale(const Vector& s) {
    Matrix scale = Matrix::identity();
    scale[0][0] = s.x;
    scale[1][1] = s.y;
    scale[2][2] = s.z;
    // concat the operation to total transformation
    concatTransform(scale);
}

void Instance::concatTransform(Matrix& M) {
    transform = product(M, transform);
    inverse = transform.invert();
}

void Instance::setMaterial(Material* m) {
    /* TODO */ NOT_IMPLEMENTED;
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ NOT_IMPLEMENTED;
}

Intersection Instance::intersect(const Ray& ray, float previousBestDistance) const {
    Ray new_ray = Ray(this->inverse * ray.o, this->inverse * ray.d);
    Intersection hit = archetype->intersect(new_ray, previousBestDistance);
    if (hit) {
        return(Intersection(hit.distance, ray, hit.solid, (this->inverse.transpose() * (hit.normalV)).normalize(), ray.getPoint(hit.distance)));
    }
    return Intersection::failure();
}

BBox Instance::getBounds() const {
    BBox b = archetype->getBounds();
    Point corners[8];
    corners[0] = Point(b.min.x, b.min.y, b.min.z);
    corners[1] = Point(b.min.x, b.min.y, b.max.z);
    corners[2] = Point(b.min.x, b.max.y, b.min.z);
    corners[3] = Point(b.min.x, b.max.y, b.max.z);
    corners[4] = Point(b.max.x, b.min.y, b.min.z);
    corners[5] = Point(b.max.x, b.min.y, b.max.z);
    corners[6] = Point(b.max.x, b.max.y, b.min.z);
    corners[7] = Point(b.max.x, b.max.y, b.max.z);
    BBox bbox = BBox::empty();
    for (uint16_t i = 0; i < 8; i++) {
        bbox.extend(transform * corners[i]);
    }
    return bbox;
}

}
