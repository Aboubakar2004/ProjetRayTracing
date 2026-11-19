#pragma once

#include "material/material.hpp"

namespace rt {

// Matte (diffuse) material using Lambert shading:
// the more the surface faces the light, the brighter it is.
//   brightness = max(0, normal . directionToLight)
//   result     = surface colour * light colour * brightness
class LambertShader : public Material {
 public:
  explicit LambertShader(const Colour& colour);

  Colour shade(const HitInfo& hit, const Light& light) const override;

 private:
  Colour _colour;
};

}  // namespace rt
