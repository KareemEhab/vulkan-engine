#pragma once

#include "device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

using namespace std;

namespace engine {
class Model {
public:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;

		static vector<VkVertexInputBindingDescription> getBindingDescriptions();
		static vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
	};

	Model(Device &device, const vector<Vertex>& vertices);
	~Model();

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void bind(VkCommandBuffer commandBuffer);
	void draw(VkCommandBuffer commandBuffer);

private:
	void createVertexBuffers(const vector<Vertex>& vertices);

	Device &device;
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	uint32_t vertexCount;
};
}