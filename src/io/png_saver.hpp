#pragma once

#include <string>

#include "io/image_saver.hpp"

namespace rt {

// Saves an image to disk as a PNG file (8-bit RGB), using LodePNG.
class PngSaver : public ImageSaver {
 public:
  // Throws std::runtime_error if the file cannot be encoded or written.
  void save(Image& image, const std::string& path) override;
};

}  // namespace rt
