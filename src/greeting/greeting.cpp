#include "greeting/greeting.hpp"

namespace rt {

std::string greeting(const std::string& name) {
  return "Hello, " + (name.empty() ? std::string("world") : name) + "!";
}

}  // namespace rt
