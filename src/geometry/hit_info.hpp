#pragma once

#include "math/vector.hpp"

namespace rt {

// Declared here, defined in material/material.hpp.
// (material.hpp includes this file, so we can't include it back.)
class Material;

// Everything we need to know about the point where a ray hits an object.
struct HitInfo {
  double t;                   // distance along the ray: point = ray.at(t)
  Vector point;               // where the ray hits the surface
  Vector normal;              // surface direction at that point (length 1)
  const Material* material;   // how to colour the surface (owned by the object)
};

}  // namespace rt
