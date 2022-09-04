#include <iostream>
#include <chrono> 

void a_julia();
void a_cameras();
void a_solids();
void a_indexing();
void a_instancing();
void a_lighting();
void a_materials();
void a_textures();
void a_local();
void a_mappers();
void a_distributed();
void a_smooth();
void a_bumpmappers();
void a_scene();

using namespace std::chrono;

int main(int argc, char* argv[]) {
    auto start = high_resolution_clock::now();

    a_scene();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << float(duration.count()) / 1000.0 << "seconds" << std::endl;

    return 0;
}