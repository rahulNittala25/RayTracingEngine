#include <rt/solids/disc.h>
#include <rt/coordmappers/world.h>
#include <core/random.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material): Solid(texMapper, material)
{
	this->center = center;
	this->normal = normal;
	this->radius = radius;


	Vector s;
	if (normal.x < normal.y && normal.x < normal.z) {
		s = Vector(0, -normal.z, normal.y).normalize();
	}
	else if (normal.y < normal.x && normal.y < normal.z) {
		s = Vector(-normal.z, 0, normal.x).normalize();
	}
	else {
		s = Vector(-normal.y, normal.x, 0).normalize();
	}
	Vector t = cross(normal, s).normalize();
	m = Matrix::system(s, t, normal.normalize());
}

BBox Disc::getBounds() const {
	Point min = center - Vector(radius, radius, radius);
	Point max = center + Vector(radius, radius, radius);
	return BBox(min, max);
}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
	if (dot(ray.d, this->normal) == 0.0) return Intersection::failure();
	float t = - dot(ray.o - center, this->normal) / dot(ray.d, this->normal);
	if (t > previousBestDistance || t < 0) return Intersection::failure();

	Point hit_point = ray.getPoint(t);
	if ((hit_point - center).length() > radius)
		return Intersection::failure();

	return Intersection(t, ray, this, this->normal, hit_point);
}

Solid::Sample Disc::sample() const {
	float u = random(), v = random();
	Point p = m * Point(u * radius * cos(2 * pi * v), u * radius * sin(2 * pi * v), 0.0f);
	Solid::Sample s;
	s.point = Point(center.x + p.x, center.y + p.y, center.z + p.z);
	s.normal = normal;
	return s;
}

float Disc::getArea() const {
	return pi * pow(radius,2);
}

}
