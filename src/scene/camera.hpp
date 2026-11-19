#pragma once

#include "image/colour.hpp"
#include "image/image.hpp"
#include "math/ray.hpp"
#include "math/vector.hpp"
#include "scene/scene.hpp"

namespace rt {

// A camera placed at a position.
// For now, it always faces the positive Z-axis.
// The screen is a rectangle at distance 1 in front of it,
// centred on the camera's line of sight, cut into imageWidth x imageHeight
// pixels.
// The position is private: use the getter to read it.
class Camera {
 public:
  explicit Camera(const Vector& position);

  // Getter: read the position.
  const Vector& position() const;

  // The ray from the camera through the centre of pixel (x, y).
  // (0, 0) is the top-left pixel. screenWidth is the width of the screen
  // in world units; its height follows the image's proportions.
  Ray rayThroughPixel(unsigned int x, unsigned int y, double screenWidth,
                      unsigned int imageWidth, unsigned int imageHeight) const;

  // The colour seen along a ray: the material of the nearest shape it hits,
  // lit by the scene's light, or black if it hits nothing.
  Colour trace(const Ray& ray, const Scene& scene) const;

  // Trace one ray per pixel and return the resulting image.
  Image render(const Scene& scene, double screenWidth,
               unsigned int imageWidth, unsigned int imageHeight) const;

 private:
  Vector _position;
};

}  // namespace rt
