#ifndef RENDERER_HPP
#define RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace Rendering{
    class VulkanInstance{
        VkInstance m_vkInstance;

        //Debug
#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else 
        const bool m_enableValidationLayers = true;
#endif
        VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
        const std::vector<const char*> m_validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };


    public:
        VulkanInstance();
        
        //Debug
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        void setupDebugMessenger();
        VkResult CreateDebugUtilsMessengerEXT(
            VkInstance instance, 
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
            const VkAllocationCallbacks* pAllocator, 
            VkDebugUtilsMessengerEXT* pDebugMessenger);

        ~VulkanInstance();
    };

    class Window{
        GLFWwindow* m_window;
    public:
        Window();
    };

    class Renderer{
        Window m_window;
        VulkanInstance m_vkInstance;
    public:
        Renderer();
    };


}

#endif
