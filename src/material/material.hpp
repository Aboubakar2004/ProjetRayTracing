#pragma once

#include "geometry/hit_info.hpp"
#include "image/colour.hpp"
#include "scene/light.hpp"

namespace rt {

// Abstract base class (Strategy pattern): decides the colour of a surface.
// Each kind of material (flat, Lambert, ...) is its own subclass.
class Material {
 public:
  virtual ~Material() = default;

  // Compute the colour of the surface at the hit point, lit by the light.
  virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};

}  // namespace rt
