cmake_minimum_required(VERSION 3.20)
project(RayTracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# LodePNG: PNG encoding. Upstream has no release tags, so it is pinned to a
# commit. It ships no CMakeLists.txt, so we build its single source file here.
include(FetchContent)
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG 7b2893e35891c0c85bee5595caafaf3c2044b409)
FetchContent_MakeAvailable(lodepng)

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
# SYSTEM: don't report our warnings for third-party headers.
target_include_directories(lodepng SYSTEM PUBLIC ${lodepng_SOURCE_DIR})

# Core library: all the logic lives here so it can be unit-tested.
add_library(raytracer_core
  src/greeting/greeting.cpp
  src/math/vector.cpp
  src/math/ray.cpp
  src/geometry/sphere.cpp
  src/scene/camera.cpp
  src/image/colour.cpp
  src/image/image.cpp
  src/io/png_saver.cpp
)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE lodepng)

# Executables
add_executable(hello app/main.cpp)
target_link_libraries(hello PRIVATE raytracer_core)

# Tests
include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
