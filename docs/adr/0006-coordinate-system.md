# 6. Coordinate system: x right, y up, z forward, pixels from the top left

## Context

The camera, the scene and the image must agree on which way is up, and where the
first pixel is. A sign mistake gives an image that is upside down or mirrored. In a
symmetric test image, such a mistake can go unnoticed.

There are two conventions to choose:

- **The world:** the y axis can point up (the usual maths and film convention) or down
  (the usual screen convention). The camera can look along +z or along -z (the OpenGL
  convention).
- **The image:** pixels can be counted from the top left (the PNG and screen convention)
  or from the bottom left.

## Decision

- **World:** x points to the right, **y points up**, and **z points forward**, away from
  the camera. The camera looks along +z, and the screen is at distance 1 in front of it.
- **Image:** pixel `(0, 0)` is the **top-left** pixel. `x` is the column, which grows to
  the right, and `y` is the row, which grows **downwards**. This matches PNG files, so the
  image is saved without flipping it.
- `Camera::rayThroughPixel` converts between the two: it takes the centre of the pixel
  (+0.5), and turns the row upside down (y on the screen = half the height − row
  position).

We did not take "y down" in the world, even though it would match the image, because
"up" would then be negative in every scene, which is error-prone for people describing
scenes.

## Status

Accepted

## Consequences

- Scenes read naturally: the floor is at a negative y, and objects in front of the
  camera have a positive z.
- The only place where y is flipped is `rayThroughPixel`. It is tested with an odd-sized,
  non-square image (5 × 3) and off-centre pixels, so a sign mistake makes a test fail.
- With z forward and x right, the axes form a left-handed system, unlike OpenGL. Anyone
  importing scenes from other tools must convert them.
