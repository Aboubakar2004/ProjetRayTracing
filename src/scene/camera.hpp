#pragma once

#include "math/vector.hpp"

namespace rt {

// A camera placed at a position.
// For now, it always faces the positive Z-axis.
// The position is private: use the getter to read it.
class Camera {
 public:
  explicit Camera(const Vector& position);

  // Getter: read the position.
  const Vector& position() const;

 private:
  Vector _position;
};

}  // namespace rt
