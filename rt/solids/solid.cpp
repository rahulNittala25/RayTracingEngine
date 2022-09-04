#include <rt/solids/solid.h>
#include <rt/coordmappers/world.h>

namespace rt {

Solid::Solid(CoordMapper* texMapper, Material* material)
{
    /* TODO */
    this->material = material;
	if (texMapper == nullptr) {
		this->texMapper = new WorldMapper(Vector::rep(1.0f));
	}
	else {
		this->texMapper = texMapper;
	}
}

}
