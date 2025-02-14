#ifndef CORE_H
#define CORE_H

#include <cstdint>
#include <optional>
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Core{
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete(){
            return graphicsFamily.has_value() && presentFamily.has_value(); 
        }
    };

    class Application{
               
        GLFWwindow* m_window;
        VkInstance m_vkInstance;
        VkDebugUtilsMessengerEXT m_debugMessenger;   
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkDevice m_device;
        VkQueue m_graphicsQueue = VK_NULL_HANDLE;
        VkQueue m_presentQueue = VK_NULL_HANDLE;
        VkSurfaceKHR m_surface = VK_NULL_HANDLE;

        
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
#ifdef NDEBUG
        const bool enableValidationLayers = false;
#else 
        const bool enableValidationLayers = true;
#endif

         public:
        Application();
 
        void Initialize();

        void InitializeWindow();

        void createInstance();
        void setupDebugMessenger(); 
        
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        bool checkValidationLayerSupport();
        
        std::vector<const char*> getRequiredExtensions();

        //Physical Devices
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        //Make Logical Devices
        void createLogicalDevice();
        
        //create Surface
        void createSurface();

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger); 

        void InitializeVulkan();

        void StartLoop();
         
        ~Application();

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT m_debugMessenger, const VkAllocationCallbacks* pAllocator);
    };
}
#endif


