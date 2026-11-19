#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/sphere.hpp"
#include "material/flat_shader.hpp"
#include "scene/camera.hpp"

using Catch::Matchers::WithinAbs;

namespace {

void requireVector(const rt::Vector& v, double x, double y, double z) {
  REQUIRE_THAT(v.x(), WithinAbs(x, 1e-9));
  REQUIRE_THAT(v.y(), WithinAbs(y, 1e-9));
  REQUIRE_THAT(v.z(), WithinAbs(z, 1e-9));
}

}  // namespace

// Screen width 5, image 5 x 3: each pixel is 1 x 1.
TEST_CASE("rayThroughPixel: centre pixel looks straight ahead", "[camera]") {
  rt::Camera camera(rt::Vector(0, 0, 0));

  rt::Ray ray = camera.rayThroughPixel(2, 1, 5, 5, 3);

  requireVector(ray.direction(), 0, 0, 1);
}

TEST_CASE("rayThroughPixel: top right pixel", "[camera]") {
  rt::Camera camera(rt::Vector(0, 0, 0));

  rt::Ray ray = camera.rayThroughPixel(4, 0, 5, 5, 3);

  requireVector(ray.direction(), 2, 1, 1);
}

TEST_CASE("rayThroughPixel: bottom left pixel", "[camera]") {
  rt::Camera camera(rt::Vector(0, 0, 0));

  rt::Ray ray = camera.rayThroughPixel(0, 2, 5, 5, 3);

  requireVector(ray.direction(), -2, -1, 1);
}

// Screen width 2, image 512 x 256: each pixel is 1/256 wide,
// the screen is 2 x 1.
TEST_CASE("rayThroughPixel: small pixels, top left pixel", "[camera]") {
  rt::Camera camera(rt::Vector(0, 0, 0));

  rt::Ray ray = camera.rayThroughPixel(0, 0, 2, 512, 256);

  requireVector(ray.direction(), -1 + 1.0 / 512, 0.5 - 1.0 / 512, 1);
}

TEST_CASE("rayThroughPixel: small pixels, bottom right pixel", "[camera]") {
  rt::Camera camera(rt::Vector(0, 0, 0));

  rt::Ray ray = camera.rayThroughPixel(511, 255, 2, 512, 256);

  requireVector(ray.direction(), 1 - 1.0 / 512, -0.5 + 1.0 / 512, 1);
}

TEST_CASE("rayThroughPixel: the ray starts at the camera", "[camera]") {
  rt::Camera camera(rt::Vector(1, 2, 3));

  rt::Ray ray = camera.rayThroughPixel(2, 1, 5, 5, 3);

  requireVector(ray.origin(), 1, 2, 3);
}

TEST_CASE("trace returns the colour of the shape hit", "[camera]") {
  rt::Scene scene(rt::Light(rt::Vector(0, 0, -100), rt::Colour(1, 1, 1)));
  auto red = std::make_shared<rt::FlatShader>(rt::Colour(1, 0, 0));
  scene.add(std::make_unique<rt::Sphere>(rt::Vector(0, 0, 9), 5, red));
  rt::Camera camera(rt::Vector(0, 0, -1));

  rt::Colour colour = camera.trace(rt::Ray(rt::Vector(0, 0, -1),
                                           rt::Vector(0, 0, 1)), scene);

  REQUIRE(colour.r() == 1);
  REQUIRE(colour.g() == 0);
  REQUIRE(colour.b() == 0);
}

TEST_CASE("trace returns black when nothing is hit", "[camera]") {
  rt::Scene scene(rt::Light(rt::Vector(0, 0, -100), rt::Colour(1, 1, 1)));
  auto red = std::make_shared<rt::FlatShader>(rt::Colour(1, 0, 0));
  scene.add(std::make_unique<rt::Sphere>(rt::Vector(0, 0, 9), 5, red));
  rt::Camera camera(rt::Vector(0, 0, -1));

  rt::Colour colour = camera.trace(rt::Ray(rt::Vector(0, 0, -1),
                                           rt::Vector(0, 1, 0)), scene);

  REQUIRE(colour.r() == 0);
  REQUIRE(colour.g() == 0);
  REQUIRE(colour.b() == 0);
}
