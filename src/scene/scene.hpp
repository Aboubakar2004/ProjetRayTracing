#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"
#include "math/ray.hpp"
#include "scene/light.hpp"

namespace rt {

// Everything that is rendered: a light and any number of shapes.
class Scene {
 public:
  explicit Scene(const Light& light);

  // The scene owns its shapes (hence std::unique_ptr and std::move).
  void add(std::unique_ptr<Shape> shape);

  // Getter: read the light.
  const Light& light() const;

  // The hit closest to the ray origin among all the shapes,
  // or std::nullopt if the ray hits nothing.
  std::optional<HitInfo> nearestHit(const Ray& ray) const;

 private:
  Light _light;
  std::vector<std::unique_ptr<Shape>> _shapes;
};

}  // namespace rt
