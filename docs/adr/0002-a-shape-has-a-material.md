# 2. A shape has a material

- **Status:** Proposed
- **Date:** 2026-11-19

## Context

Every object in the scene (sphere, plane, ...) needs two separate things:

- **geometry:** where a ray hits it, and the normal at that point;
- **appearance:** what colour that point has under a light.

We could make the appearance part of the shape through inheritance
(`RedSphere`, `LambertSphere`, `FlatPlane`, ...). But every new shape × every new
material would then need its own class.

## Decision

**Composition: a shape *has* a material, it *is not* one.**

- `Shape` is an interface (`intersect(ray)`) implemented by `Sphere` and `Plane`.
  It only knows geometry.
- `Material` is an interface (`shade(hit, light)`), following the Strategy pattern.
  It is implemented by `FlatShader` (a fixed colour) and `LambertShader` (Lambert's law:
  brightness = max(0, normal · direction to light)).
- Each shape receives its material in its constructor, as a
  `std::shared_ptr<const Material>`, so several shapes can share one material.
- When a ray hits a shape, the `HitInfo` it returns carries a pointer to that material.
  The camera then calls `hit->material->shade(*hit, light)` without knowing which
  shape or material it is.

## Consequences

- A new shape (e.g. a cylinder) is one new `Shape` class. A new material (e.g. a mirror)
  is one new `Material` class. No existing class changes (open/closed principle), and
  any shape can use any material.
- Shapes and materials can each be tested on their own.
- `HitInfo` holds a non-owning pointer to the material. It is only valid while the
  shape that returned it is alive. In practice, the scene owns the shapes for the
  whole render.
- This differs from the course reference, where `Material` is one concrete class and
  `Hit` stores a copy of it. We kept the Strategy version so that new kinds of material
  can be added without changing `Material`.
