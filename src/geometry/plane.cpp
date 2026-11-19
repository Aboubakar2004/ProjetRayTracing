#include "geometry/plane.hpp"

#include <utility>

namespace rt {

Plane::Plane(const Vector& point, const Vector& normal,
             std::shared_ptr<const Material> material)
    : _point(point), _normal(normal.normalised()), _material(std::move(material)) {}

std::optional<HitInfo> Plane::intersect(const Ray& ray) const {
  // A point P is on the plane if normal . (P - point) = 0.
  // With P = origin + t * direction:
  //   t = normal . (point - origin) / (normal . direction)
  double normalDotDirection = _normal.dot(ray.direction());
  if (normalDotDirection == 0.0) {
    return std::nullopt;  // the ray is parallel to the plane
  }

  double t = _normal.dot(_point - ray.origin()) / normalDotDirection;
  if (t <= 0.0) {
    return std::nullopt;  // the plane is behind the ray
  }

  return HitInfo{t, ray.at(t), _normal, _material.get()};
}

}  // namespace rt
