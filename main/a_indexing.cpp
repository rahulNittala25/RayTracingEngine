
#include <core/assert.h>
#include <core/scalar.h>
#include <core/image.h>
#include <rt/world.h>
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/groups/bvh.h>
#include <rt/solids/sphere.h>
#include <rt/cameras/perspective.h>
#include <rt/integrators/casting.h>

using namespace rt;

void a_indexing() {
    Image img(800, 600);

    BVH* scene = new BVH();
    scene->add(new Sphere(Point(2.5f,  .5f,  -1), 0.5  , nullptr, nullptr));
    scene->add(new Sphere(Point(2.5f,  -1.f,  -1), 0.5, nullptr, nullptr));
    scene->add(new Sphere(Point(4.5f,  .5f,  -1), 0.5 , nullptr, nullptr));

    loadOBJ(scene, "models/", "cow.obj");

    // low poly objects - PerspectiveCamera cam3(Point(300,50,0)...
    /*loadOBJ(scene, "models/", "plant.obj");
    loadOBJ(scene, "models/", "deer.obj");
    loadOBJ(scene, "models/", "cat.obj");*/

    // sitting - PerspectiveCamera cam3(Point(7000,400,0)
    // loadOBJ(scene, "models/", "sitting.obj");

	scene->rebuildIndex();
    World world;
    world.scene = scene;

    // x:diagonal move y: z:this sets up-down
    PerspectiveCamera cam1(Point(-8.85f, -7.85f, 7.0f), Vector(1.0f,1.0f,-0.6f), Vector(0, 0, 1), pi/8, pi/6);
    PerspectiveCamera cam2(Point(16.065f, -12.506f, 1.771f), Point(-0.286f, -0.107f, 1.35f)-Point(16.065f, -12.506f, 1.771f), Vector(0, 0, 1), pi/8, pi/6);
    //PerspectiveCamera cam3(Point(300,50,0), Vector(-1, 0, 0), Vector(0, 1, 0), pi/8, pi/6);
    RayCastingIntegrator integrator(&world);

    Renderer engine1(&cam1, &integrator);
    engine1.render(img);
    img.writePNG("a3-1.png");

    //Renderer engine2(&cam2, &integrator);
    //engine2.render(img);
    //img.writePNG("a3-2.png");

    /*Renderer engine3(&cam3, &integrator);
    engine3.render(img);
    img.writePNG("a3-3.png");*/
}
