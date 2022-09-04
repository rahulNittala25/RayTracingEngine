cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
  # Please add your source files here
)

set(ASSIGNMENT_SOURCES
  core/image.h
  core/color.h
  core/random.h

  rt/world.h
  rt/renderer.h
  rt/loaders/obj.h
  rt/integrators/recraytrace.h
  rt/integrators/casting.h

  rt/groups/simplegroup.h
  rt/groups/bvh.h

  rt/cameras/perspective.h
  rt/cameras/dofperspective.h
  rt/solids/quad.h
  rt/solids/sphere.h
  rt/solids/triangle.h
  rt/solids/disc.h
  rt/solids/infiniteplane.h
  rt/solids/aabox.h
  rt/solids/environmentsolid.h
  rt/primmod/bmap.h
  rt/textures/constant.h
  rt/textures/imagetex.h
  rt/textures/perlin.h

  rt/materials/flatmaterial.h
  rt/materials/lambertian.h
  rt/materials/fuzzymirror.h
  rt/materials/glass.h
  rt/materials/phong.h
  rt/materials/combine.h
  rt/materials/cooktorrance.h
  rt/materials/mirror.h
  rt/materials/dummy.h

  rt/lights/arealight.h
  rt/lights/pointlight.h
  rt/lights/spotlight.h
  rt/lights/directional.h

  rt/primmod/instance.h
  rt/coordmappers/plane.h
  rt/coordmappers/spherical.h
  rt/coordmappers/tmapper.h
  rt/coordmappers/environment.h
  ${MY_ADDITIONAL_SOURCES}
  main/a_scene.cpp
)

file(COPY
  models/Book1.mtl
  models/Book1.obj
  models/Book2.mtl
  models/Book2.obj
  models/Bottle.mtl
  models/Bottle.obj
  models/Chair.mtl
  models/Chair.obj
  models/Chair1.mtl
  models/Chair1.obj
  models/Computer.mtl
  models/Computer.obj
  models/ComputerScreen.mtl
  models/ComputerScreen.obj
  models/EnvMap.png
  models/floor_texture.png
  models/MetalBottle.mtl
  models/MetalBottle.obj
  models/Monitor_Screen.png
  models/Mouse.mtl
  models/Mouse.obj
  models/Paper_tex.png
  models/Paper_weight.mtl
  models/Paper_weight.obj
  models/Pens2.mtl
  models/Pens2.obj
  models/Table.mtl
  models/Table.obj
  models/TableLamp.mtl
  models/TableLamp.obj
  models/Walls.mtl
  models/Walls.obj
DESTINATION ${CMAKE_BINARY_DIR}/models
)
