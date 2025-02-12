#ifndef CORE_H
#define CORE_H

#include <vector>
#include <vulkan/vulkan_core.h>
#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Core{
    class Application{
               
        GLFWwindow* m_window;
        VkInstance m_vkInstance;
        VkDebugUtilsMessengerEXT debugMessenger;   
        
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

        bool checkValidationLayerSupport();
        
        std::vector<const char*> getRequiredExtensions();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData) {

        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

            return VK_FALSE;
        }

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger); 

        void InitializeVulkan();

        void StartLoop();
         
        void CleanUp();

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    };
}
#endif


