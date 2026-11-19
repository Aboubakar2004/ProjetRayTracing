#include "geometry/sphere.hpp"

#include <cmath>
#include <utility>

namespace rt {

Sphere::Sphere(const Vector& center, double radius,
               std::shared_ptr<const Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {}

const Vector& Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }
const Material& Sphere::material() const { return *_material; }

std::optional<HitInfo> Sphere::intersect(const Ray& ray) const {
  // A point P is on the sphere if |P - center|^2 = radius^2.
  // With P = origin + t * direction, this gives a*t^2 + b*t + c = 0.
  Vector originToCenter = ray.origin() - _center;
  double a = ray.direction().dot(ray.direction());
  double b = 2.0 * originToCenter.dot(ray.direction());
  double c = originToCenter.dot(originToCenter) - _radius * _radius;

  double discriminant = b * b - 4.0 * a * c;
  if (discriminant < 0) {
    return std::nullopt;  // the ray misses the sphere
  }

  // The two solutions, smallest first.
  double sqrtDiscriminant = std::sqrt(discriminant);
  double t1 = (-b - sqrtDiscriminant) / (2.0 * a);
  double t2 = (-b + sqrtDiscriminant) / (2.0 * a);

  // Closest hit in front of the ray origin.
  double t;
  if (t1 >= 0) {
    t = t1;
  } else if (t2 >= 0) {
    t = t2;  // the ray starts inside the sphere
  } else {
    return std::nullopt;  // the sphere is behind the ray
  }

  Vector point = ray.at(t);
  Vector normal = (point - _center).normalised();
  return HitInfo{point, normal, _material.get()};
}

}  // namespace rt
