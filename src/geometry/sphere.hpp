#pragma once

#include "math/vector.hpp"

namespace rt {

// A sphere: a center point and a radius.
// The members are private: use the getters to read them.
class Sphere {
 public:
  Sphere(const Vector& center, double radius);

  // Getters: read the center and the radius.
  const Vector& center() const;
  double radius() const;

 private:
  Vector _center;
  double _radius;
};

}  // namespace rt
