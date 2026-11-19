#pragma once

#include "material/material.hpp"
#include "math/vector.hpp"

namespace rt {

// Everything we need to know about the point where a ray hits an object.
struct HitInfo {
  Vector point;               // where the ray hits the surface
  Vector normal;              // surface direction at that point (length 1)
  const Material* material;   // how to colour the surface (owned by the object)
};

}  // namespace rt
