#include "scene/scene.hpp"

#include <utility>

namespace rt {

Scene::Scene(const Light& light) : _light(light) {}

void Scene::add(std::unique_ptr<Shape> shape) {
  _shapes.push_back(std::move(shape));
}

const Light& Scene::light() const { return _light; }

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
  std::optional<HitInfo> nearest;
  for (const std::unique_ptr<Shape>& shape : _shapes) {
    std::optional<HitInfo> hit = shape->intersect(ray);
    // Keep this hit if it is the first one, or closer than the best so far.
    if (hit && (!nearest || hit->t < nearest->t)) {
      nearest = hit;
    }
  }
  return nearest;
}

}  // namespace rt
