#pragma once

#include <memory>
#include <optional>

#include "geometry/shape.hpp"
#include "material/material.hpp"
#include "math/vector.hpp"

namespace rt {

// An infinite flat surface (e.g. the floor), defined by one point on it
// and its normal (the direction it faces).
class Plane : public Shape {
 public:
  // The normal does not need to have length 1: it is normalised here.
  Plane(const Vector& point, const Vector& normal,
        std::shared_ptr<const Material> material);

  std::optional<HitInfo> intersect(const Ray& ray) const override;

 private:
  Vector _point;
  Vector _normal;
  std::shared_ptr<const Material> _material;
};

}  // namespace rt
