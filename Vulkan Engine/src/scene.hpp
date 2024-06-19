#pragma once

#include "device.hpp"
#include "window.hpp"
#include "game_object.hpp"
#include "renderer.hpp"

// std
#include <memory>
#include <vector>

using namespace std;

namespace engine {
	class Scene {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		Scene();
		~Scene();

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		void run();

	private:
		void loadGameObjects();

		Window window{ WIDTH, HEIGHT, "Vulkan Engine" };
		Device device{ window };
		Renderer renderer{ window, device };
		std::vector<GameObject> gameObjects;
	};
}