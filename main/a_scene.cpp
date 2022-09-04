#include <core/image.h>
#include <core/color.h>
#include <core/random.h>

#include <rt/world.h>   
#include <rt/renderer.h>
#include <rt/loaders/obj.h>
#include <rt/integrators/recraytrace.h>
#include <rt/integrators/casting.h>

#include <rt/groups/simplegroup.h>
#include <rt/groups/bvh.h>

#include <rt/cameras/perspective.h>
#include <rt/cameras/dofperspective.h>
#include <rt/solids/quad.h>
#include <rt/solids/sphere.h>
#include <rt/solids/triangle.h>
#include <rt/solids/disc.h>
#include <rt/solids/infiniteplane.h>
#include <rt/solids/aabox.h>
#include <rt/solids/environmentsolid.h>
#include <rt/primmod/bmap.h>
#include <rt/textures/constant.h>
#include <rt/textures/imagetex.h>
#include <rt/textures/perlin.h>

#include <rt/materials/flatmaterial.h>
#include <rt/materials/lambertian.h>
#include <rt/materials/fuzzymirror.h>
#include <rt/materials/glass.h>
#include <rt/materials/phong.h>
#include <rt/materials/combine.h>
#include <rt/materials/cooktorrance.h>
#include <rt/materials/mirror.h>
#include <rt/materials/dummy.h>

#include <rt/lights/arealight.h>
#include <rt/lights/pointlight.h>
#include <rt/lights/spotlight.h>
#include <rt/lights/directional.h>

#include <rt/primmod/instance.h>
#include <rt/coordmappers/plane.h>
#include <rt/coordmappers/spherical.h>
#include <rt/coordmappers/tmapper.h>
#include <rt/coordmappers/environment.h>

using namespace rt;

ConstantTexture* black_tex = new ConstantTexture(RGBColor::rep(0.0f));
ConstantTexture* white_tex = new ConstantTexture(RGBColor::rep(1.0f));

void a_scene() {
    Image img(1920, 1080);

    SimpleGroup* scene = new SimpleGroup();


    World world;
    world.scene = scene;


    ConstantTexture* red_tex = new ConstantTexture(RGBColor(1.0f, 0.0f, 0.0f));
    Sphere* block1 = new Sphere(Point(4, 0.5001, 10.0f), 0.5, nullptr, new MirrorMaterial(0.37, 2.82));
    scene->add(block1);

    ImageTexture* paper_tex = new ImageTexture("models/Paper_tex.png", ImageTexture::BorderHandlingType::REPEAT);

    TriangleMapper* paper_plane_bl = new TriangleMapper(Point(1, 0, 0), Point(0, 0, 0), Point(0, 1, 0));
    TriangleMapper* paper_plane_tr = new TriangleMapper(Point(1, 1, 0), Point(1, 0, 0), Point(0, 1, 0));
    Triangle* paper_tr = new Triangle(Point(-7.75, 0.0001, 20), Point(1.25, 0.0001, 20), Point(1.25, 0.0001, 4), paper_plane_bl, new LambertianMaterial(black_tex, paper_tex));
    Triangle* paper_bl = new Triangle(Point(-7.75, 0.0001, 4), Point(-7.75, 0.0001, 20), Point(1.25, 0.0001, 4), paper_plane_tr, new LambertianMaterial(black_tex, paper_tex));

    scene->add(paper_bl);
    scene->add(paper_tr);


    BVH* pens = new BVH();
    ConstantTexture* col1 = new ConstantTexture(RGBColor(0, 0, 0.57));
    ConstantTexture* col2 = new ConstantTexture(RGBColor(0.341, 0.341, 0.341));
    ConstantTexture* col3 = new ConstantTexture(RGBColor(0.703, 0, 0));
    MatLib* pens_matlib = new MatLib();
    pens_matlib->insert(std::pair<std::string, Material*>("blinn3", new LambertianMaterial(black_tex, col1)));
    pens_matlib->insert(std::pair<std::string, Material*>("blinn4", new LambertianMaterial(black_tex, col2)));
    pens_matlib->insert(std::pair<std::string, Material*>("blinn5", new LambertianMaterial(black_tex, col3)));
    pens_matlib->insert(std::pair<std::string, Material*>("blinn6", new LambertianMaterial(black_tex, white_tex)));
    loadOBJ(pens, "models/", "Pens2.obj", pens_matlib);
    pens->rebuildIndex();
    scene->add(pens);

    BVH* table = new BVH();
    MatLib* table_matlib = new MatLib();
    ImageTexture* tex1 = new ImageTexture("models/floor_texture.png", ImageTexture::BorderHandlingType::MIRROR);
    CombineMaterial* comb1 = new CombineMaterial();
    comb1->add(new LambertianMaterial(black_tex, tex1), 0.9);
    comb1->add(new MirrorMaterial(2.485f, 3.433f), 0.05);
    comb1->add(new PhongMaterial(white_tex, 10.0), 0.05);
    table_matlib->insert(std::pair<std::string, Material*>("ComputerDesk1Black", comb1));
    loadOBJ(table, "models/", "Table.obj", table_matlib);
    table->rebuildIndex();
    scene->add(table);

    BVH* table_lamp = new BVH();
    MatLib* table_lamp_matlib = new MatLib();
    ConstantTexture* cream_tex = new ConstantTexture(RGBColor(255 / 255.0, 253 / 255.0, 208 / 255.0));
    CombineMaterial* comb2 = new CombineMaterial();
    comb2->add(new LambertianMaterial(black_tex, cream_tex), 0.75);
    comb2->add(new CookTorranceMaterial(cream_tex, 0.8f, 0.3f, 0.06f), 0.25);
    table_lamp_matlib->insert(std::pair<std::string, Material*>("lambert1", comb2));
    table_lamp_matlib->insert(std::pair<std::string, Material*>("lambert3", comb2));
    loadOBJ(table_lamp, "models/", "TableLamp.obj", table_lamp_matlib);
    table_lamp->rebuildIndex();
    scene->add(table_lamp);

    BVH* bottle = new BVH();
    MatLib* bottle_matlib = new MatLib();
    FuzzyMirrorMaterial* fuzzy_bottle = new FuzzyMirrorMaterial(2.485, 3.433, pi / 36);
    LambertianMaterial* bottle_link = new LambertianMaterial(black_tex, new ConstantTexture(RGBColor(47 / 255.0, 79 / 255.0, 79 / 255.0)));
    LambertianMaterial* btl = new LambertianMaterial(black_tex, black_tex);
    bottle_matlib->insert(std::pair<std::string, Material*>("Material.002", fuzzy_bottle));
    bottle_matlib->insert(std::pair<std::string, Material*>("Material.003", bottle_link));
    bottle_matlib->insert(std::pair<std::string, Material*>("Material.004", btl));
    loadOBJ(bottle, "models/", "Bottle.obj", bottle_matlib);
    bottle->rebuildIndex();
    scene->add(bottle);

    BVH* books = new BVH();
    MatLib* books_matlib = new MatLib();
    LambertianMaterial* book_cover = new LambertianMaterial(black_tex, new ConstantTexture(RGBColor(82 / 255.0, 50 / 255.0, 17 / 255.0)));
    LambertianMaterial* book_pages = new LambertianMaterial(black_tex, white_tex);
    books_matlib->insert(std::pair<std::string, Material*>("Hojas", book_pages));
    books_matlib->insert(std::pair<std::string, Material*>("libro", book_cover));
    loadOBJ(books, "models/", "Book1.obj", books_matlib);
    loadOBJ(books, "models/", "Book2.obj", books_matlib);
    books->rebuildIndex();
    scene->add(books);

    BVH* monitor = new BVH();
    MatLib* monitor_matlib = new MatLib();
    ConstantTexture* matte_black_tex = new ConstantTexture(RGBColor(40 / 255.0, 40 / 255.0, 43 / 255.0));
    LambertianMaterial* monitor_material = new LambertianMaterial(black_tex, matte_black_tex);
    monitor_matlib->insert(std::pair<std::string, Material*>("TVGovde", monitor_material));
    loadOBJ(monitor, "models/", "Computer.obj", monitor_matlib);
    monitor->rebuildIndex();
    scene->add(monitor);


    ImageTexture* screen_tex = new ImageTexture("models/Monitor_Screen.png", ImageTexture::BorderHandlingType::MIRROR);
    TriangleMapper* screen_plane_bl = new TriangleMapper(Point(0, 1, 0), Point(1, 1, 0), Point(0, 0, 0));
    TriangleMapper* screen_plane_tr = new TriangleMapper(Point(1, 0, 0), Point(0, 0, 0), Point(1, 1, 0));
    Triangle* screen_bl = new Triangle(Point(-3.756444, 5.061831, -69.850922), Point(15.292376, 5.061830, -26.873314), Point(-3.756444, 31.079197, -69.850922), screen_plane_bl, new LambertianMaterial(screen_tex, black_tex));
    Triangle* screen_tr = new Triangle(Point(15.292376, 31.079193, -26.873314), Point(-3.756444, 31.079197, -69.850922), Point(15.292376, 5.061830, -26.873314), screen_plane_tr, new LambertianMaterial(screen_tex, black_tex));
    scene->add(screen_bl);
    scene->add(screen_tr);


    BVH* Chair = new BVH();
    MatLib* chair_matlib = new MatLib();
    LambertianMaterial* chair_red = new LambertianMaterial(black_tex, new ConstantTexture(RGBColor(0.419,0,0)));
    PhongMaterial* chair_gloss = new PhongMaterial(matte_black_tex, 5);
    chair_matlib->insert(std::pair<std::string, Material*>("Chair", chair_red));
    chair_matlib->insert(std::pair<std::string, Material*>("Chair.001", chair_red));
    chair_matlib->insert(std::pair<std::string, Material*>("Metal", chair_gloss));
    chair_matlib->insert(std::pair<std::string, Material*>("Steel_Black_Polished", chair_gloss));
    chair_matlib->insert(std::pair<std::string, Material*>("Steel_White", chair_gloss));
    loadOBJ(Chair, "models/", "Chair1.obj", chair_matlib);
    Chair->rebuildIndex();
    scene->add(Chair);

    BVH* Mouse = new BVH();
    MatLib* mouse_matlib = new MatLib();
    CombineMaterial* comb3 = new CombineMaterial();
    comb3->add(new LambertianMaterial(black_tex, matte_black_tex), 0.9);
    comb3->add(new PhongMaterial(cream_tex, 10), 0.1);
    mouse_matlib->insert(std::pair<std::string, Material*>("Mouse_tex",comb3));
    mouse_matlib->insert(std::pair<std::string, Material*>("TrackBall", new LambertianMaterial(black_tex, white_tex)));
    loadOBJ(Mouse, "models/", "Mouse.obj", mouse_matlib);
    Mouse->rebuildIndex();
    scene->add(Mouse);


    ConstantTexture* orange_tex = new ConstantTexture(RGBColor(1, 0.2, 0.1));
    InfinitePlane* wall1 = new InfinitePlane(Point(35.079830, -86.177078, 229.902786), Vector(-1,0,0), nullptr, new LambertianMaterial(black_tex, orange_tex));
    InfinitePlane* wall2 = new InfinitePlane(Point(-169.105927, 94.843552, -106.312248), Vector(0, 0, 1), nullptr, new LambertianMaterial(black_tex, orange_tex));
    InfinitePlane* floor = new InfinitePlane(Point(70.578781, -85.535484, -109.853340), Vector(0, 1, 0), nullptr, new LambertianMaterial(black_tex, cream_tex));
    InfinitePlane* roof = new InfinitePlane(Point(-65, 120.0f, 12), Vector(0, -1, 0), nullptr, new LambertianMaterial(black_tex, cream_tex));
    scene->add(wall1);
    scene->add(wall2);
    scene->add(floor);
    scene->add(roof);


    ConstantTexture* lightsrctex = new ConstantTexture(RGBColor::rep(35.0f)*3);
    Material* lightsource = new LambertianMaterial(lightsrctex, black_tex);

    Quad* light = new Quad(Point(-65, 110.0f, 12), Vector(0, 0, 40), Vector(-40, 0, 0), nullptr, lightsource);
    AreaLight als(light);
    world.light.push_back(&als);
    scene->add(light);


    PerspectiveCamera cam1(Point(-11.961111, 31.278305, 111.595787), (Point(-11.899755, 31.056065, 110.622726) - Point(-11.961111, 31.278305, 111.595787)).normalize(), Vector(0.013986, 0.974992, -0.221801), (pi * 270) / (5 * 480), pi / 5);


    RecursiveRayTracingIntegrator integrator(&world);




    Renderer engine1(&cam1, &integrator);
    engine1.setSamples(1000);
    engine1.render(img);
    img.writePNG("Submission_Ready_1920x1080_1000.png");

}
