#include <rt/solids/openCylinder.h>
#include <rt/coordmappers/world.h>
#include <core/float4.h>
#include <rt/solids/disc.h>

namespace rt {
	Cylinder::Cylinder(float radius1, float radius2, float limit1, float limit2, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
	{
		this->radius1 = radius1;
		this->radius2 = radius2;
		assert(radius1 < radius2);
		this->limit1 = limit1;
		this->limit2 = limit2;
		assert(limit1 < limit2);
	}
	BBox Cylinder::getBounds() const
	{
		BBox bbox = BBox(Point(-radius2, -radius2, limit1), Point(radius2, radius2, limit2));
		return bbox;
	}
	Intersection Cylinder::intersect(const Ray& ray, float previousBestDistance) const
	{
		float a = pow(ray.d.x, 2) + pow(ray.d.y, 2);
		float b = 2 * (ray.o.x * ray.d.x + ray.o.y * ray.d.y);
		float c1 = pow(ray.d.x, 2) + pow(ray.d.y, 2) - pow(radius1,2);
		float c2 = pow(ray.d.x, 2) + pow(ray.d.y, 2) - pow(radius2, 2);
		float bestDist = previousBestDistance;
		float check1 = b * b - 4 * a * c1, check2 = b * b - 4 * a * c2;
		int hit_surface = -1;
		if (check1 > 0) {
			float dist1 = (-b + sqrt(check1)) / (2 * a);
			float dist2 = (-b - sqrt(check1)) / (2 * a);
			Point pt1 = ray.getPoint(dist1);
			Point pt2 = ray.getPoint(dist2);
			if (limit1 < dist1 && dist1 < limit2 && dist1 < bestDist) {
				bestDist = dist1;
				hit_surface = 0;  //Hit inside the cylinder
			}
			if (limit1 < dist2 && dist2 < limit2 && dist2 < bestDist) {
				bestDist = dist2;
				hit_surface = 0;  //Hit inside the cylinder
			}
		}
		if (check2 > 0) {
			float dist1 = (-b + sqrt(check2)) / (2 * a);
			float dist2 = (-b - sqrt(check2)) / (2 * a);
			Point pt1 = ray.getPoint(dist1);
			Point pt2 = ray.getPoint(dist2);
			if (limit1 < dist1 && dist1 < limit2 && dist1 < bestDist) {
				bestDist = dist1;
				hit_surface = 1;  //Hit outside the cylinder
			}
			if (limit1 < dist2 && dist2 < limit2 && dist2 < bestDist) {
				bestDist = dist2;
				hit_surface = 1;  //Hit outside the cylinder
			}
		}
		Intersection top_hit = (Disc(Point(0, 0, limit2), Vector(0, 0, 1), radius2, nullptr, nullptr)).intersect(ray, bestDist);
		if (top_hit && top_hit.distance < bestDist && radius1<top_hit.distance && top_hit.distance<radius2) {
			bestDist = top_hit.distance;
			hit_surface = 2;
		}
		Intersection bot_hit = (Disc(Point(0, 0, limit1), Vector(0, 0, 1), radius1, nullptr, nullptr)).intersect(ray, bestDist);
		if (bot_hit && bot_hit.distance < bestDist) {
			bestDist = bot_hit.distance;
			hit_surface = 3;
		}
		Point hitP = ray.getPoint(bestDist);
		switch (hit_surface)
		{
		case 0: return Intersection(bestDist, ray, this, Vector(-hitP.x, -hitP.y, 0), ray.getPoint(bestDist));
		case 1:  return Intersection(bestDist, ray, this, Vector(hitP.x, hitP.y, 0), ray.getPoint(bestDist));
		case 2:  return Intersection(bestDist, ray, this, Vector(0, 0, 1), ray.getPoint(bestDist));
		case 3: return Intersection(bestDist, ray, this, Vector(0, 0, -1), ray.getPoint(bestDist));
		default:
			break;
		}
		return Intersection::failure();
	}
	Solid::Sample Cylinder::sample() const
	{
		NOT_IMPLEMENTED;
	}
	float Cylinder::getArea() const
	{
		return pi*pow(radius2,2)*(limit2 - limit1);
	}
}
