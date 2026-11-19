#pragma once

#include "material/material.hpp"

namespace rt {

// The simplest material: always returns the same colour,
// with no lighting.
class FlatShader : public Material {
 public:
  explicit FlatShader(const Colour& colour);

  Colour shade() const override;

 private:
  Colour _colour;
};

}  // namespace rt
