#include "scene.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>


int main() {
	engine::Scene app{};

	try {
		app.run();
	}
	catch (const exception& e) {
		cout << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}