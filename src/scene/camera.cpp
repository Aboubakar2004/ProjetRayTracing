#include "scene/camera.hpp"

namespace rt {

Camera::Camera(const Vector& position) : _position(position) {}

const Vector& Camera::position() const { return _position; }

}  // namespace rt
