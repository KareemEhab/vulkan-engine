#include "model.hpp"

#include <cassert>
#include <cstring>

namespace engine {
Model::Model(Device& device, const vector<Vertex>& vertices) : device(device) {
	createVertexBuffers(vertices);
}

Model::~Model() {
	vkDestroyBuffer(device.device(), vertexBuffer, nullptr);
	vkFreeMemory(device.device(), vertexBufferMemory, nullptr);
}

void Model::createVertexBuffers(const vector<Vertex>& vertices) {
	vertexCount = static_cast<uint32_t>(vertices.size());
	assert(vertexCount >= 3 && "Vertex count must be at least 3");
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
	device.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		vertexBuffer,
		vertexBufferMemory
	);
	void* data;
	vkMapMemory(device.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
	vkUnmapMemory(device.device(), vertexBufferMemory);
	// Since we have HOST_COHERENT_BIT the data will be automatically flushed from the Host *data variable* (CPU) to the device (GPU) 
}

void Model::draw(VkCommandBuffer commandBuffer) {
	vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
}

void Model::bind(VkCommandBuffer commandBuffer) {
	VkBuffer buffers[] = { vertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

vector<VkVertexInputBindingDescription> Model::Vertex::getBindingDescriptions() {
	vector<VkVertexInputBindingDescription> bindingDescriptions(1);
	bindingDescriptions[0].binding = 0;
	bindingDescriptions[0].stride = sizeof(Vertex);
	bindingDescriptions[0].binding = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescriptions;
}

vector<VkVertexInputAttributeDescription> Model::Vertex::getAttributeDescriptions() {
	vector<VkVertexInputAttributeDescription> attributeDescriptions(2);

	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(Vertex, position); // Or 0 as the position starts from index 0

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(Vertex, color);

	return attributeDescriptions;
}
}