#pragma once

#include "math/vector.hpp"

namespace rt {

// A ray: a starting point (origin) and a direction.
// The members are private: use the getters to read them.
class Ray {
 public:
  Ray(const Vector& origin, const Vector& direction);

  // Getters: read the origin and the direction.
  const Vector& origin() const;
  const Vector& direction() const;

  // The point at distance t along the ray: origin + t * direction.
  Vector at(double t) const;

 private:
  Vector _origin;
  Vector _direction;
};

}  // namespace rt
