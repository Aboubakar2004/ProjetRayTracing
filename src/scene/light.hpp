#pragma once

#include "image/colour.hpp"
#include "math/vector.hpp"

namespace rt {

// A point light: light coming from a single point in space,
// shining equally in every direction.
// The members are private: use the getters to read them.
class Light {
 public:
  Light(const Vector& position, const Colour& colour);

  // Getters: read the position and the colour.
  const Vector& position() const;
  const Colour& colour() const;

 private:
  Vector _position;
  Colour _colour;
};

}  // namespace rt
