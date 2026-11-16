#include <catch2/catch_test_macros.hpp>

#include "greeting.hpp"

TEST_CASE("greeting addresses the given name", "[greeting]") {
  REQUIRE(rt::greeting("Alice") == "Hello, Alice!");
}

TEST_CASE("greeting defaults to world", "[greeting]") {
  REQUIRE(rt::greeting() == "Hello, world!");
}
