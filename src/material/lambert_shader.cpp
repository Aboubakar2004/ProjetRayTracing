#include "material/lambert_shader.hpp"

#include <algorithm>

namespace rt {

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) const {
  Vector directionToLight = (light.position() - hit.point).normalised();

  // 1 when the surface faces the light, 0 when it is side-on.
  // Negative means the light is behind the surface: no light at all.
  double brightness = std::max(0.0, hit.normal.dot(directionToLight));

  return _colour * light.colour() * brightness;
}

}  // namespace rt
