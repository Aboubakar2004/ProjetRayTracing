#include "geometry/sphere.hpp"

namespace rt {

Sphere::Sphere(const Vector& center, double radius)
    : _center(center), _radius(radius) {}

const Vector& Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }

}  // namespace rt
