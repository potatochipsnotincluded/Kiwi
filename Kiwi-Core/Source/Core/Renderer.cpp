#include "Renderer.h"

namespace Kiwi {

    void Renderer::Init()
    {
        using namespace Kiwi;

        VulkanData* vk = Window::GetVulkanData();
        glm::vec2 size = Window::GetSize();
        uint32_t width = static_cast<uint32_t>(size.x);
        uint32_t height = static_cast<uint32_t>(size.y);

        VkSwapchainCreateInfoKHR swapchainInfo{};
        swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainInfo.surface = vk->surface;
        swapchainInfo.minImageCount = 2;
        swapchainInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
        swapchainInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        swapchainInfo.imageExtent = { width, height };
        swapchainInfo.imageArrayLayers = 1;
        swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
        swapchainInfo.clipped = VK_TRUE;

        KW_ASSERT(vkCreateSwapchainKHR(vk->device, &swapchainInfo, nullptr, &m_Swapchain) == VK_SUCCESS);

        uint32_t imageCount = 0;
        vkGetSwapchainImagesKHR(vk->device, m_Swapchain, &imageCount, nullptr);
        m_SwapchainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(vk->device, m_Swapchain, &imageCount, m_SwapchainImages.data());

        // -- Create Image Views
        m_SwapchainImageViews.resize(imageCount);
        for (uint32_t i = 0; i < imageCount; ++i)
        {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = m_SwapchainImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = swapchainInfo.imageFormat;
            viewInfo.components = {
                VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
                VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY
            };
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            KW_ASSERT(vkCreateImageView(vk->device, &viewInfo, nullptr, &m_SwapchainImageViews[i]) == VK_SUCCESS);
        }

        // -- Render Pass
        VkAttachmentDescription colourAttachment{};
        colourAttachment.format = swapchainInfo.imageFormat;
        colourAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colourAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colourAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colourAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colourAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colourAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colourAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colourAttachmentRef{};
        colourAttachmentRef.attachment = 0;
        colourAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colourAttachmentRef;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colourAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;

        KW_ASSERT(vkCreateRenderPass(vk->device, &renderPassInfo, nullptr, &m_RenderPass) == VK_SUCCESS);

        // -- Framebuffers
        m_Framebuffers.resize(imageCount);
        for (size_t i = 0; i < imageCount; ++i)
        {
            VkFramebufferCreateInfo fbInfo{};
            fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            fbInfo.renderPass = m_RenderPass;
            fbInfo.attachmentCount = 1;
            fbInfo.pAttachments = &m_SwapchainImageViews[i];
            fbInfo.width = width;
            fbInfo.height = height;
            fbInfo.layers = 1;

            KW_ASSERT(vkCreateFramebuffer(vk->device, &fbInfo, nullptr, &m_Framebuffers[i]) == VK_SUCCESS);
        }

        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        KW_ASSERT(vkCreateSemaphore(vk->device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphore) == VK_SUCCESS);
        KW_ASSERT(vkCreateSemaphore(vk->device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphore) == VK_SUCCESS);

        m_CommandBuffers.resize(m_SwapchainImages.size());

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = vk->graphicsQueueIndex;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        KW_ASSERT(vkCreateCommandPool(vk->device, &poolInfo, nullptr, &m_CommandPool) == VK_SUCCESS);

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = m_CommandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = static_cast<uint32_t>(m_CommandBuffers.size());

        KW_ASSERT(vkAllocateCommandBuffers(vk->device, &allocInfo, m_CommandBuffers.data()) == VK_SUCCESS);
    }

	void Renderer::Clear(glm::vec4 colour)
	{
        VkExtent2D m_SwapchainExtent{};
        glm::vec2 size = Kiwi::Window::GetSize();
        m_SwapchainExtent.width = static_cast<uint32_t>(size.x);
        m_SwapchainExtent.height = static_cast<uint32_t>(size.y);

        VulkanData* vk = Kiwi::Window::GetVulkanData();
        
        vkAcquireNextImageKHR(vk->device, m_Swapchain, UINT64_MAX, m_ImageAvailableSemaphore, VK_NULL_HANDLE, &m_ImageIndex);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        KW_ASSERT(vkBeginCommandBuffer(m_CommandBuffers[m_ImageIndex], &beginInfo) == VK_SUCCESS);

        VkClearValue clearColor = { colour.r, colour.g, colour.b, colour.a };

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = m_RenderPass;
        renderPassInfo.framebuffer = m_Framebuffers[m_ImageIndex];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = m_SwapchainExtent;
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(m_CommandBuffers[m_ImageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void Renderer::Present()
	{
        vkCmdEndRenderPass(m_CommandBuffers[m_ImageIndex]);

        KW_ASSERT(vkEndCommandBuffer(m_CommandBuffers[m_ImageIndex]) == VK_SUCCESS);

        m_CurrentImageIndex = m_ImageIndex;

        VulkanData* vk = Kiwi::Window::GetVulkanData();

        VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphore };
        VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphore };

        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_CommandBuffers[m_CurrentImageIndex];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        KW_ASSERT(vkQueueSubmit(vk->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) == VK_SUCCESS);

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &m_Swapchain;
        presentInfo.pImageIndices = &m_CurrentImageIndex;

        vkQueuePresentKHR(vk->graphicsQueue, &presentInfo);

        vkQueueWaitIdle(vk->graphicsQueue);
	}

}
