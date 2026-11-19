#pragma once

namespace rt {

// A colour with red, green and blue components.
// The components are private: use the getters to read them.
class Colour {
 public:
  Colour(double r, double g, double b);

  // Getters: read the components.
  double r() const;
  double g() const;
  double b() const;

  // Lets you write: c3 = c1 * c2; (multiplies each component,
  // e.g. a red surface lit by a white light stays red)
  Colour operator*(const Colour& other) const;

  // Lets you write: c2 = c1 * 0.5; (darkens or brightens)
  Colour operator*(double scalar) const;

 private:
  double _r;
  double _g;
  double _b;
};

}  // namespace rt
