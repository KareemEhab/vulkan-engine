
#include "scene.hpp"

// std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
  engine::Scene app{};

  try {
    app.run();
  } catch (const std::exception &e) {
    cout << e.what() << endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}