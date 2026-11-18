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

 private:
  double _r;
  double _g;
  double _b;
};

}  // namespace rt
