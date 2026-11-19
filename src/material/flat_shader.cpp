#include "material/flat_shader.hpp"

namespace rt {

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(const HitInfo& /*hit*/, const Light& /*light*/) const {
  return _colour;
}

}  // namespace rt
