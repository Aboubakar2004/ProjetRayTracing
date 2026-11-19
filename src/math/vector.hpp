#pragma once

namespace rt {

// A 3D vector with components x, y and z.
// The components are private: use the getters to read them.
class Vector {
 public:
  Vector(double x, double y, double z);

  // Getters: read the components.
  double x() const;
  double y() const;
  double z() const;

  // Lets you write: v3 = v1 + v2;
  Vector operator+(const Vector& other) const;

  // Lets you write: v3 = v1 - v2;
  Vector operator-(const Vector& other) const;

  // Lets you write: v2 = v1 * 2;
  Vector operator*(double scalar) const;

  // Dot product: x1*x2 + y1*y2 + z1*z2.
  double dot(const Vector& other) const;

  // Returns this vector divided by its length: same direction, length 1.
  // Not valid for the zero vector (its length is 0).
  Vector normalised() const;

 private:
  double _x;
  double _y;
  double _z;
};

// Lets you write: v2 = 2 * v1;
// Not a member of Vector, because the number is on the left.
Vector operator*(double scalar, const Vector& v);

}  // namespace rt
