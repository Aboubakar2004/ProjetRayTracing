#include "io/png_saver.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

#include <lodepng.h>

namespace rt {

namespace {

// Convert a colour component in [0, 1] to a byte in [0, 255].
// Values outside [0, 1] are clamped.
unsigned char toByte(double component) {
  double clamped = std::clamp(component, 0.0, 1.0);
  return static_cast<unsigned char>(std::lround(clamped * 255.0));
}

}  // namespace

void PngSaver::save(Image& image, const std::string& path) {
  const unsigned int width = image.width();
  const unsigned int height = image.height();

  // LodePNG expects the pixels row by row from the top-left, 3 bytes each.
  std::vector<unsigned char> bytes;
  bytes.reserve(static_cast<std::size_t>(width) * height * 3);
  for (unsigned int y = 0; y < height; ++y) {
    for (unsigned int x = 0; x < width; ++x) {
      const Colour& pixel = image.getPixel(x, y);
      bytes.push_back(toByte(pixel.r()));
      bytes.push_back(toByte(pixel.g()));
      bytes.push_back(toByte(pixel.b()));
    }
  }

  unsigned int error = lodepng::encode(path, bytes, width, height, LCT_RGB, 8);
  if (error != 0) {
    throw std::runtime_error("PngSaver: could not save '" + path +
                             "': " + lodepng_error_text(error));
  }
}

}  // namespace rt
