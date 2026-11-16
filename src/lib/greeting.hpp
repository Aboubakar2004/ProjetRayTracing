#pragma once

#include <string>

namespace rt {

// Returns "Hello, <name>!" (or "Hello, world!" when name is empty).
std::string greeting(const std::string& name = "");

}  // namespace rt
