#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/sphere.hpp"
#include "material/flat_shader.hpp"

using Catch::Matchers::WithinAbs;

namespace {

std::shared_ptr<const rt::Material> red() {
  return std::make_shared<rt::FlatShader>(rt::Colour(1, 0, 0));
}

}  // namespace

TEST_CASE("a ray hitting a sphere returns the closest hit point", "[sphere]") {
  auto material = red();
  rt::Sphere sphere(rt::Vector(0, 0, 5), 1, material);
  rt::Ray ray(rt::Vector(0, 0, 0), rt::Vector(0, 0, 1));

  auto hit = sphere.intersect(ray);

  REQUIRE(hit.has_value());
  // Hit point: front of the sphere, at z = 4 (not the back at z = 6).
  REQUIRE_THAT(hit->point.x(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(hit->point.y(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(hit->point.z(), WithinAbs(4, 1e-9));
  // Normal: from the center to the hit point, length 1.
  REQUIRE_THAT(hit->normal.x(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(hit->normal.y(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(hit->normal.z(), WithinAbs(-1, 1e-9));
  // Material: the sphere's own material.
  REQUIRE(hit->material == material.get());
}

TEST_CASE("a ray missing a sphere returns no hit", "[sphere]") {
  rt::Sphere sphere(rt::Vector(0, 0, 5), 1, red());
  rt::Ray ray(rt::Vector(0, 0, 0), rt::Vector(0, 1, 0));

  REQUIRE_FALSE(sphere.intersect(ray).has_value());
}

TEST_CASE("a sphere behind the ray returns no hit", "[sphere]") {
  rt::Sphere sphere(rt::Vector(0, 0, -5), 1, red());
  rt::Ray ray(rt::Vector(0, 0, 0), rt::Vector(0, 0, 1));

  REQUIRE_FALSE(sphere.intersect(ray).has_value());
}

TEST_CASE("a ray starting inside a sphere hits its far side", "[sphere]") {
  rt::Sphere sphere(rt::Vector(0, 0, 0), 1, red());
  rt::Ray ray(rt::Vector(0, 0, 0), rt::Vector(0, 0, 1));

  auto hit = sphere.intersect(ray);

  REQUIRE(hit.has_value());
  REQUIRE_THAT(hit->point.z(), WithinAbs(1, 1e-9));
  REQUIRE_THAT(hit->normal.z(), WithinAbs(1, 1e-9));
}
