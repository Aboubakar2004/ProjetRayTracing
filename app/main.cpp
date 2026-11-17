#include <iostream>

#include "greeting/greeting.hpp"

int main(int argc, char** argv) {
  std::cout << rt::greeting(argc > 1 ? argv[1] : "") << '\n';
  return 0;
}
