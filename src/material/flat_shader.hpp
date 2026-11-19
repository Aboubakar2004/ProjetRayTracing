#pragma once

#include "material/material.hpp"

namespace rt {

// The simplest material: always returns the same colour,
// ignoring the hit point and the light.
class FlatShader : public Material {
 public:
  explicit FlatShader(const Colour& colour);

  Colour shade(const HitInfo& hit, const Light& light) const override;

 private:
  Colour _colour;
};

}  // namespace rt
