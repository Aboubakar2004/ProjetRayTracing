#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/plane.hpp"
#include "material/flat_shader.hpp"

using Catch::Matchers::WithinAbs;

namespace {

std::shared_ptr<const rt::Material> green() {
  return std::make_shared<rt::FlatShader>(rt::Colour(0, 1, 0));
}

}  // namespace

TEST_CASE("a ray going down hits the floor", "[plane]") {
  auto material = green();
  rt::Plane floor(rt::Vector(0, 0, 0), rt::Vector(0, 1, 0), material);
  rt::Ray ray(rt::Vector(0, 8, 0), rt::Vector(3, -4, 0));

  auto hit = floor.intersect(ray);

  REQUIRE(hit.has_value());
  REQUIRE_THAT(hit->t, WithinAbs(2, 1e-9));
  REQUIRE_THAT(hit->point.x(), WithinAbs(6, 1e-9));
  REQUIRE_THAT(hit->point.y(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(hit->point.z(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(hit->normal.y(), WithinAbs(1, 1e-9));
  REQUIRE(hit->material == material.get());
}

TEST_CASE("a tilted plane returns its normal with length 1", "[plane]") {
  // The line 3x + 4y = 24: normal (3, 4, 0), of length 5.
  rt::Plane plane(rt::Vector(8, 0, 0), rt::Vector(3, 4, 0), green());
  rt::Ray ray(rt::Vector(-8, 0, 0), rt::Vector(4, 3, 0));

  auto hit = plane.intersect(ray);

  REQUIRE(hit.has_value());
  REQUIRE_THAT(hit->t, WithinAbs(2, 1e-9));
  REQUIRE_THAT(hit->point.x(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(hit->point.y(), WithinAbs(6, 1e-9));
  REQUIRE_THAT(hit->normal.x(), WithinAbs(0.6, 1e-9));
  REQUIRE_THAT(hit->normal.y(), WithinAbs(0.8, 1e-9));
  REQUIRE_THAT(hit->normal.z(), WithinAbs(0, 1e-9));
}

TEST_CASE("a ray parallel to the plane misses it", "[plane]") {
  rt::Plane floor(rt::Vector(0, 0, 0), rt::Vector(0, 1, 0), green());
  rt::Ray ray(rt::Vector(0, 8, 0), rt::Vector(5, 0, 0));

  REQUIRE_FALSE(floor.intersect(ray).has_value());
}

TEST_CASE("a plane behind the ray is not hit", "[plane]") {
  rt::Plane floor(rt::Vector(0, 0, 0), rt::Vector(0, 1, 0), green());
  rt::Ray ray(rt::Vector(0, 8, 0), rt::Vector(3, 4, 0));  // going up

  REQUIRE_FALSE(floor.intersect(ray).has_value());
}
