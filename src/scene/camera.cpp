#include "scene/camera.hpp"

#include <optional>

#include "material/material.hpp"

namespace rt {

Camera::Camera(const Vector& position) : _position(position) {}

const Vector& Camera::position() const { return _position; }

Ray Camera::rayThroughPixel(unsigned int x, unsigned int y, double screenWidth,
                            unsigned int imageWidth,
                            unsigned int imageHeight) const {
  // All pixels are square, so the screen height follows from the width.
  double pixelSize = screenWidth / imageWidth;
  double screenHeight = pixelSize * imageHeight;

  // Centre of the pixel, measured from the centre of the screen.
  // x grows to the right; y grows upwards (rows go downwards).
  double screenX = (x + 0.5) * pixelSize - screenWidth / 2;
  double screenY = screenHeight / 2 - (y + 0.5) * pixelSize;

  return Ray(_position, Vector(screenX, screenY, 1));
}

Colour Camera::trace(const Ray& ray, const Scene& scene) const {
  std::optional<HitInfo> hit = scene.nearestHit(ray);
  if (!hit) {
    return Colour(0, 0, 0);  // nothing hit: black background
  }
  return hit->material->shade(*hit, scene.light());
}

Image Camera::render(const Scene& scene, double screenWidth,
                     unsigned int imageWidth, unsigned int imageHeight) const {
  Image image(imageWidth, imageHeight);
  for (unsigned int y = 0; y < imageHeight; ++y) {
    for (unsigned int x = 0; x < imageWidth; ++x) {
      Ray ray = rayThroughPixel(x, y, screenWidth, imageWidth, imageHeight);
      image.setPixel(x, y, trace(ray, scene));
    }
  }
  return image;
}

}  // namespace rt
