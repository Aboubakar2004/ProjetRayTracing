#include <catch2/catch_test_macros.hpp>

#include "math/ray.hpp"

TEST_CASE("at(t) returns the point at distance t along the ray", "[ray]") {
  rt::Ray ray(rt::Vector(1, 2, 3), rt::Vector(0, 0, 1));

  rt::Vector point = ray.at(2);

  REQUIRE(point.x() == 1);
  REQUIRE(point.y() == 2);
  REQUIRE(point.z() == 5);
}

TEST_CASE("at(0) returns the origin of the ray", "[ray]") {
  rt::Ray ray(rt::Vector(1, 2, 3), rt::Vector(4, 5, 6));

  rt::Vector point = ray.at(0);

  REQUIRE(point.x() == 1);
  REQUIRE(point.y() == 2);
  REQUIRE(point.z() == 3);
}
