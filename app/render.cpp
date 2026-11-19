// Renders the milestone m1 scene: a red ball on a grey floor.
// Usage: ./build/debug/render [output.png]   (default: image.png)
#include <iostream>
#include <memory>
#include <string>

#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "io/png_saver.hpp"
#include "material/lambert_shader.hpp"
#include "scene/camera.hpp"
#include "scene/light.hpp"
#include "scene/scene.hpp"

int main(int argc, char** argv) {
  std::string path = argc > 1 ? argv[1] : "image.png";

  // The sun: a white light very far away in the direction (-1, 1, -1)
  // (up, left, behind the camera), so its rays are almost parallel.
  rt::Light sun(rt::Vector(-1, 1, -1) * 1000, rt::Colour(1, 1, 1));
  rt::Scene scene(sun);

  auto red = std::make_shared<rt::LambertShader>(rt::Colour(1, 0, 0));
  auto grey = std::make_shared<rt::LambertShader>(rt::Colour(0.8, 0.8, 0.8));

  // A red ball of radius 5, resting on the floor at y = -5.
  scene.add(std::make_unique<rt::Sphere>(rt::Vector(0, 0, 9), 5, red));
  scene.add(std::make_unique<rt::Plane>(rt::Vector(0, -5, 0),
                                        rt::Vector(0, 1, 0), grey));

  // Eye at z = -1, so the screen (distance 1 in front) is at z = 0.
  rt::Camera camera(rt::Vector(0, 0, -1));
  rt::Image image = camera.render(scene, 2.0, 400, 300);

  rt::PngSaver saver;
  saver.save(image, path);
  std::cout << "Saved " << path << '\n';
  return 0;
}
