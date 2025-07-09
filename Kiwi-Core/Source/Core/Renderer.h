#pragma once
#include "Common.h"

#include "Debug.h"

#include "Window.h"

namespace Kiwi {

	class Renderer
	{
	public:
		void Init();

		void Clear(glm::vec4 colour);

		void Present();

	private:
		VkSwapchainKHR m_Swapchain{};
		std::vector<VkImage> m_SwapchainImages;
		std::vector<VkImageView> m_SwapchainImageViews;

		VkRenderPass m_RenderPass{};
		std::vector<VkFramebuffer> m_Framebuffers;

		VkSemaphore m_ImageAvailableSemaphore{};
		VkSemaphore m_RenderFinishedSemaphore{};
		VkCommandPool m_CommandPool{};
		std::vector<VkCommandBuffer> m_CommandBuffers;
		uint32_t m_CurrentImageIndex = 0;

		uint32_t m_ImageIndex;
	};

}