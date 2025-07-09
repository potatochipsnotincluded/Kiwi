#pragma once
#include "Common.h"

#include <glm/glm.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Kiwi {

	struct VulkanData
	{
		VkInstance instance = VK_NULL_HANDLE;
		VkDevice device;
		VkPhysicalDevice physicalDevice;
		VkSurfaceKHR surface;
		VkQueue graphicsQueue;
		uint32_t graphicsQueueIndex;
	};

	const char* VkResultToString(VkResult result);

	namespace Window {

		// Public
		void Init(std::string_view title, int width, int height);

		void Update();

		void Shutdown();

		bool ShouldClose();

		bool IsKeyPressed(uint32_t key);

		bool IsMouseButtonPressed(uint32_t button);

		glm::vec2 GetMousePosition();

		VulkanData* GetVulkanData();

		glm::vec2 GetSize();
		
		// Private
		inline GLFWwindow* m_Window;

		inline VulkanData* m_VulkanData;

	}

}