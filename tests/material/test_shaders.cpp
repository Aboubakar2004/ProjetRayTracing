#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>

#include "material/flat_shader.hpp"
#include "material/lambert_shader.hpp"

using Catch::Matchers::WithinAbs;

namespace {

// A hit at the origin, on a surface facing up (+Y).
rt::HitInfo hitFacingUp(const rt::Material& material) {
  return rt::HitInfo{1, rt::Vector(0, 0, 0), rt::Vector(0, 1, 0), &material};
}

const rt::Colour white(1, 1, 1);

}  // namespace

TEST_CASE("flat shader ignores the light", "[shader]") {
  rt::FlatShader shader(rt::Colour(1, 0.5, 0));
  rt::Light light(rt::Vector(0, -10, 0), white);  // below the surface

  rt::Colour result = shader.shade(hitFacingUp(shader), light);

  REQUIRE(result.r() == 1);
  REQUIRE(result.g() == 0.5);
  REQUIRE(result.b() == 0);
}

TEST_CASE("lambert: light straight above gives the full surface colour",
          "[shader]") {
  rt::LambertShader shader(rt::Colour(1, 0.5, 0));
  rt::Light light(rt::Vector(0, 10, 0), white);

  rt::Colour result = shader.shade(hitFacingUp(shader), light);

  REQUIRE_THAT(result.r(), WithinAbs(1, 1e-9));
  REQUIRE_THAT(result.g(), WithinAbs(0.5, 1e-9));
  REQUIRE_THAT(result.b(), WithinAbs(0, 1e-9));
}

TEST_CASE("lambert: light at 60 degrees gives half the colour", "[shader]") {
  rt::LambertShader shader(rt::Colour(1, 1, 1));
  // Direction to the light: (sqrt(3), 1, 0) / 2, so cos(angle) = 0.5.
  rt::Light light(rt::Vector(std::sqrt(3.0), 1, 0), white);

  rt::Colour result = shader.shade(hitFacingUp(shader), light);

  REQUIRE_THAT(result.r(), WithinAbs(0.5, 1e-9));
  REQUIRE_THAT(result.g(), WithinAbs(0.5, 1e-9));
  REQUIRE_THAT(result.b(), WithinAbs(0.5, 1e-9));
}

TEST_CASE("lambert: light behind the surface gives black", "[shader]") {
  rt::LambertShader shader(rt::Colour(1, 1, 1));
  rt::Light light(rt::Vector(0, -10, 0), white);

  rt::Colour result = shader.shade(hitFacingUp(shader), light);

  REQUIRE(result.r() == 0);
  REQUIRE(result.g() == 0);
  REQUIRE(result.b() == 0);
}

TEST_CASE("lambert: the light colour tints the surface", "[shader]") {
  rt::LambertShader shader(rt::Colour(1, 1, 1));
  rt::Light light(rt::Vector(0, 10, 0), rt::Colour(1, 0, 0));  // red light

  rt::Colour result = shader.shade(hitFacingUp(shader), light);

  REQUIRE_THAT(result.r(), WithinAbs(1, 1e-9));
  REQUIRE_THAT(result.g(), WithinAbs(0, 1e-9));
  REQUIRE_THAT(result.b(), WithinAbs(0, 1e-9));
}
