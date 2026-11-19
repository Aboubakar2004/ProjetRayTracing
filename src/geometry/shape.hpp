#pragma once

#include <optional>

#include "geometry/hit_info.hpp"
#include "math/ray.hpp"

namespace rt {

// Interface for every object a ray can hit (sphere, plane, ...).
// Adding a new kind of shape = adding a new subclass;
// the scene, the camera and the materials don't change.
class Shape {
 public:
  virtual ~Shape() = default;

  // Contract: the nearest hit in front of the ray origin (t > 0),
  // with a normal of length 1, or std::nullopt if there is none.
  virtual std::optional<HitInfo> intersect(const Ray& ray) const = 0;
};

}  // namespace rt
