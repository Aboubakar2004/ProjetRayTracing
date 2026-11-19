#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/vector.hpp"

TEST_CASE("adding two vectors adds each component", "[vector]") {
  rt::Vector a(1, 2, 3);
  rt::Vector b(4, 5, 6);

  rt::Vector result = a + b;

  REQUIRE(result.x() == 5);
  REQUIRE(result.y() == 7);
  REQUIRE(result.z() == 9);
}

TEST_CASE("subtracting two vectors subtracts each component", "[vector]") {
  rt::Vector a(-1, 4, 0);
  rt::Vector b(-5, 2, 1);

  rt::Vector result = a - b;

  REQUIRE(result.x() == 4);
  REQUIRE(result.y() == 2);
  REQUIRE(result.z() == -1);
}

TEST_CASE("multiplying a vector by a number scales each component", "[vector]") {
  rt::Vector v(1, -2, 3);

  rt::Vector result = v * 2;

  REQUIRE(result.x() == 2);
  REQUIRE(result.y() == -4);
  REQUIRE(result.z() == 6);
}

TEST_CASE("multiplying a number by a vector scales each component", "[vector]") {
  rt::Vector v(1, -2, 3);

  rt::Vector result = 2 * v;

  REQUIRE(result.x() == 2);
  REQUIRE(result.y() == -4);
  REQUIRE(result.z() == 6);
}

TEST_CASE("normalising a vector divides it by its length", "[vector]") {
  using Catch::Matchers::WithinAbs;
  rt::Vector v(3, 4, 0);  // length 5

  rt::Vector result = v.normalised();

  REQUIRE_THAT(result.x(), WithinAbs(3.0 / 5.0, 1e-9));
  REQUIRE_THAT(result.y(), WithinAbs(4.0 / 5.0, 1e-9));
  REQUIRE_THAT(result.z(), WithinAbs(0.0, 1e-9));
}

TEST_CASE("the dot product sums the products of the components", "[vector]") {
  rt::Vector a(1, 2, 3);
  rt::Vector b(4, -5, 6);

  REQUIRE(a.dot(b) == 12);  // 1*4 + 2*(-5) + 3*6
}
