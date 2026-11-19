#pragma once

#include <string>

#include "image/image.hpp"

namespace rt {

// Abstract base class for anything that can save an image to a file
// (e.g. as a PNG).
class ImageSaver {
 public:
  virtual ~ImageSaver() = default;

  // Save the image to the file at the given path.
  virtual void save(Image& image, const std::string& path) = 0;
};

}  // namespace rt
