#ifndef CORE_H
#define CORE_H
#include <cstdint>
#include <cwchar>
#include <optional>
#include <vector>
#include <vulkan/vulkan_core.h>
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
    
    const int MAX_FRAMES_IN_FLIGHT = 2;

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class Application{
               
        GLFWwindow* m_window;
        VkInstance m_vkInstance;
        VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;   
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkDevice m_device = VK_NULL_HANDLE;
        VkQueue m_graphicsQueue = VK_NULL_HANDLE;
        VkQueue m_presentQueue = VK_NULL_HANDLE;
        VkSurfaceKHR m_surface = VK_NULL_HANDLE;
        VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;
        std::vector<VkImage> m_swapChainImages;
        VkFormat m_swapChainImageFormat;
        VkExtent2D m_swapChainExtent;
        std::vector<VkImageView> m_swapChainImageViews;
        VkPipelineLayout m_pipelineLayout;
        VkRenderPass m_renderPass;
        VkPipeline m_graphicsPipeline;
        std::vector<VkFramebuffer> m_swapChainFramebuffers;
        VkCommandPool m_commandPool;
        std::vector<VkCommandBuffer> m_commandBuffers;
        std::vector<VkSemaphore> m_imageAvailableSemaphores;
        std::vector<VkSemaphore> m_renderFinishedSemaphores;
        std::vector<VkFence> m_inFlightFences;
        uint32_t currentFrame = 0;
        bool framebufferResized = false;

       
        const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };
        const std::vector<const char*> m_deviceExtensions = {
VK_KHR_SWAPCHAIN_EXTENSION_NAME
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

        //Recreation Of Swap chain
        void cleanUpSwapChain();
        void reCreateSwapChain();
        
        //create Surface
        void createSurface();

        //Make swap chain
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);    
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);  
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats); 
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();

        //Make ImageViews 
        void createImageViews();

        //Create Render Pipeline
        void createGraphicsPipeline();
        VkShaderModule createShaderModule(const std::vector<char>& code);       
        void createRenderPass();

        //Create Frame Buffers
        void createFramebuffers();

        //Create Command Buffer
        void createCommandPool();
        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

        //Drawing to Frame
        void drawFrame();
        void createSyncObjects();

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger); 

        void InitializeVulkan();
        
        void StartLoop();
         
        ~Application();

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT m_debugMessenger, const VkAllocationCallbacks* pAllocator);

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
            auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
            app->framebufferResized = true;
        }
    };
}
#endif


