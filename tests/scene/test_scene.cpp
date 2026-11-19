#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "material/flat_shader.hpp"
#include "scene/scene.hpp"

using Catch::Matchers::WithinAbs;

namespace {

const rt::Light light(rt::Vector(0, 0, -100), rt::Colour(1, 1, 1));
const rt::Ray ray(rt::Vector(0, 0, -1), rt::Vector(0, 0, 1));

std::unique_ptr<rt::Shape> redSphere(const rt::Vector& center) {
  auto red = std::make_shared<rt::FlatShader>(rt::Colour(1, 0, 0));
  return std::make_unique<rt::Sphere>(center, 5, red);
}

// A wall facing the camera, crossing the z axis at z.
std::unique_ptr<rt::Shape> blueWall(double z) {
  auto blue = std::make_shared<rt::FlatShader>(rt::Colour(0, 0, 1));
  return std::make_unique<rt::Plane>(rt::Vector(0, 0, z),
                                     rt::Vector(0, 0, -1), blue);
}

}  // namespace

// Each case adds the shapes in both orders: the result must not
// depend on which shape comes first.

TEST_CASE("nearestHit: wall in front of the sphere", "[scene]") {
  // Wall hit at t = 3, sphere hit at t = 5.
  SECTION("sphere added first") {
    rt::Scene scene(light);
    scene.add(redSphere(rt::Vector(0, 0, 9)));
    scene.add(blueWall(2));

    auto hit = scene.nearestHit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3, 1e-9));
  }
  SECTION("wall added first") {
    rt::Scene scene(light);
    scene.add(blueWall(2));
    scene.add(redSphere(rt::Vector(0, 0, 9)));

    auto hit = scene.nearestHit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(3, 1e-9));
  }
}

TEST_CASE("nearestHit: sphere in front of the wall", "[scene]") {
  // Sphere hit at t = 5, wall hit at t = 21.
  SECTION("sphere added first") {
    rt::Scene scene(light);
    scene.add(redSphere(rt::Vector(0, 0, 9)));
    scene.add(blueWall(20));

    auto hit = scene.nearestHit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, 1e-9));
  }
  SECTION("wall added first") {
    rt::Scene scene(light);
    scene.add(blueWall(20));
    scene.add(redSphere(rt::Vector(0, 0, 9)));

    auto hit = scene.nearestHit(ray);
    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5, 1e-9));
  }
}

TEST_CASE("nearestHit: a ray hitting nothing returns no hit", "[scene]") {
  rt::Scene scene(light);
  scene.add(redSphere(rt::Vector(6, 0, 9)));

  REQUIRE_FALSE(scene.nearestHit(ray).has_value());
}

TEST_CASE("nearestHit: an empty scene returns no hit", "[scene]") {
  rt::Scene scene(light);

  REQUIRE_FALSE(scene.nearestHit(ray).has_value());
}
