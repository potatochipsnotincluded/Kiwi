#include "Window.h"

#include "Debug.h"

namespace Kiwi {

    const char* VkResultToString(VkResult result)
    {
        switch (result)
        {
        case VK_SUCCESS: return "VK_SUCCESS";
        case VK_NOT_READY: return "VK_NOT_READY";
        case VK_TIMEOUT: return "VK_TIMEOUT";
        case VK_EVENT_SET: return "VK_EVENT_SET";
        case VK_EVENT_RESET: return "VK_EVENT_RESET";
        case VK_INCOMPLETE: return "VK_INCOMPLETE";
        case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
        case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
        case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
        case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
        case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
        case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
        case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
        default: return "UNKNOWN_ERROR";
        }
    }

    void Window::Init(std::string_view title, int width, int height)
    {
        KW_ASSERT(glfwInit() == GLFW_TRUE);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_Window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        KW_ASSERT(m_Window);

        m_VulkanData = new VulkanData();

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions = std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);

        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Kiwi Application";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Kiwi Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = (uint32_t)extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();

        const char* validationLayers[] = { "VK_LAYER_KHRONOS_validation" };
        createInfo.enabledLayerCount = 1;
        createInfo.ppEnabledLayerNames = validationLayers;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &m_VulkanData->instance);

        if (result != VK_SUCCESS)
        {
            KW_LOG("vkCreateInstance result was " << VkResultToString(result));
            KW_ASSERT(false);
        }

        KW_ASSERT(glfwCreateWindowSurface(m_VulkanData->instance, m_Window, nullptr, &m_VulkanData->surface) == VK_SUCCESS);

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_VulkanData->instance, &deviceCount, nullptr);
        KW_ASSERT(deviceCount > 0);

        std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(m_VulkanData->instance, &deviceCount, physicalDevices.data());
        m_VulkanData->physicalDevice = physicalDevices[0];

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(m_VulkanData->physicalDevice, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_VulkanData->physicalDevice, &queueFamilyCount, queueFamilies.data());

        int graphicsQueueIndex = -1;
        for (int i = 0; i < static_cast<int>(queueFamilies.size()); ++i)
        {
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(m_VulkanData->physicalDevice, i, m_VulkanData->surface, &presentSupport);

            if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && presentSupport)
            {
                graphicsQueueIndex = i;
                break;
            }
        }

        KW_ASSERT(graphicsQueueIndex != -1);
        m_VulkanData->graphicsQueueIndex = graphicsQueueIndex;

        float queuePriority = 1.0f;
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = graphicsQueueIndex;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        const char* deviceExtensions[] = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        size_t enabledExtensionCount = 1;

        VkDeviceCreateInfo deviceCreateInfo{};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.enabledExtensionCount = enabledExtensionCount;
        deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;

        KW_ASSERT(vkCreateDevice(m_VulkanData->physicalDevice, &deviceCreateInfo, nullptr, &m_VulkanData->device) == VK_SUCCESS);

        vkGetDeviceQueue(m_VulkanData->device, graphicsQueueIndex, 0, &m_VulkanData->graphicsQueue);
    }

	void Window::Update()
	{
		glfwSwapBuffers(m_Window);
		
		glfwPollEvents();
	}

	void Window::Shutdown()
	{
        delete m_VulkanData;
		glfwTerminate();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	bool Window::IsKeyPressed(uint32_t key)
	{
        return glfwGetKey(m_Window, key) == GLFW_PRESS;
	}

	bool Window::IsMouseButtonPressed(uint32_t button)
	{
		return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
	}

	glm::vec2 Window::GetMousePosition()
	{
        double x;
        double y;
        glfwGetCursorPos(m_Window, &x, &y);

		return glm::vec2(x, y);
	}

    VulkanData* Window::GetVulkanData()
    {
        return m_VulkanData;
    }

    glm::vec2 Window::GetSize()
    {
        int32_t w;
        int32_t h;
        glfwGetWindowSize(m_Window, &w, &h);

        return glm::vec2(w, h);
    }

}