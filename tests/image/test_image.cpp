#include <catch2/catch_test_macros.hpp>

#include "image/image.hpp"

TEST_CASE("setPixel sets only the pixel at the given column and row", "[image]") {
  rt::Image image(5, 4);
  rt::Colour red(1, 0, 0);

  image.setPixel(3, 2, red);

  for (unsigned int y = 0; y < image.height(); ++y) {
    for (unsigned int x = 0; x < image.width(); ++x) {
      const rt::Colour& pixel = image.getPixel(x, y);
      if (x == 3 && y == 2) {
        REQUIRE(pixel.r() == 1);
        REQUIRE(pixel.g() == 0);
        REQUIRE(pixel.b() == 0);
      } else {
        REQUIRE(pixel.r() == 0);
        REQUIRE(pixel.g() == 0);
        REQUIRE(pixel.b() == 0);
      }
    }
  }
}
