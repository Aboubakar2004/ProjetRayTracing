#pragma once

#include <vector>

#include "image/colour.hpp"

namespace rt {

// An image of width x height pixels.
// Pixel (0, 0) is the top-left corner: x is the column, y is the row.
// Every pixel starts black.
class Image {
 public:
  Image(unsigned int width, unsigned int height);

  // Getters: read the size.
  unsigned int width() const;
  unsigned int height() const;

  // Set the pixel at column x, row y.
  void setPixel(unsigned int x, unsigned int y, const Colour& colour);

  // Read the pixel at column x, row y.
  const Colour& getPixel(unsigned int x, unsigned int y) const;

 private:
  unsigned int _width;
  unsigned int _height;
  // Pixels stored row by row: pixel (x, y) is at index y * _width + x.
  std::vector<Colour> _pixels;
};

}  // namespace rt
