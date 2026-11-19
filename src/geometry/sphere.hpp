#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.hpp"
#include "geometry/shape.hpp"
#include "material/material.hpp"
#include "math/ray.hpp"
#include "math/vector.hpp"

namespace rt {

// A sphere: a center point, a radius and a material.
// The members are private: use the getters to read them.
class Sphere : public Shape {
 public:
  // The material is shared: several shapes can use the same one.
  Sphere(const Vector& center, double radius,
         std::shared_ptr<const Material> material);

  // Getters: read the center, the radius and the material.
  const Vector& center() const;
  double radius() const;
  const Material& material() const;

  std::optional<HitInfo> intersect(const Ray& ray) const override;

 private:
  Vector _center;
  double _radius;
  std::shared_ptr<const Material> _material;
};

}  // namespace rt
