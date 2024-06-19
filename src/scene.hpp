#pragma once

#include "io/window.hpp"
#include "graphics/pipeline.hpp"
#include "graphics/swap_chain.hpp"
#include "device.hpp"

#include <memory>
#include <vector>

using namespace std;

namespace engine {
	class Scene {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT= 600;

		Scene();
		~Scene();

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		void run();
	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		Window window{ WIDTH, HEIGHT, "Vulakn Engine" };
		Device device{ window };
		SwapChain swapChain{device, window.getExtent()};
		unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		vector<VkCommandBuffer> commandBuffers;
	};
}