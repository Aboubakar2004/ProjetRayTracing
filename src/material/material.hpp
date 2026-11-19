#pragma once

#include "image/colour.hpp"

namespace rt {

// Abstract base class (Strategy pattern): decides the colour of a surface.
// Each kind of material (flat, diffuse, ...) is its own subclass.
class Material {
 public:
  virtual ~Material() = default;

  // Compute the colour of the surface.
  virtual Colour shade() const = 0;
};

}  // namespace rt
