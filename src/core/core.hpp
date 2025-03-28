#ifndef CORE_H
#define CORE_H
#define GLM_FORCE_RADIANS
#include <cstdint>
#include <cwchar>
#include <glm/ext/scalar_uint_sized.hpp>
#include <optional>
#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h> 

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

    struct Vertex{
        glm::vec2 pos;
        glm::vec3 color;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            return attributeDescriptions;
        }
    };

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
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

        VkDescriptorSetLayout m_descriptorSetLayout;
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

        VkBuffer m_vertexBuffer;
        VkDeviceMemory m_vertexBufferMemory;
        VkBuffer m_indexBuffer;
        VkDeviceMemory m_indexBufferMemory;

        std::vector<VkBuffer> m_uniformBuffers;
        std::vector<VkDeviceMemory> m_uniformBuffersMemory;
        std::vector<void*> m_uniformBuffersMapped;
        VkDescriptorPool m_descriptorPool;;
        std::vector<VkDescriptorSet> m_descriptorSets;


        const std::vector<Vertex> m_vertices = {
            {{0.0f,0.0f}, {0.1f, 0.1f, 0.1f}},
            {{0.0f,0.5f}, {1.0f, 0.0f, 0.0f}},
            {{-0.433012701892f, 0.25f}, {0.707106781187f, 0.0f, 0.707106781187f}},
            {{-0.433012701892, -0.25f}, {0.0f, 0.0f, 1.0f}},
            {{-0.0f, -0.5f}, {0.0f, 0.707106781187f, 0.707106781187f}},
            {{0.433012701892, -0.25f}, {0.0f, 1.0f, 0.0f}},
            {{0.433012701892, 0.25f}, {0.707106781187f, 0.707106781187f, 0.0f}},
        };
        
        const std::vector<uint16_t> m_indices = {
            0 ,1 ,2 ,
            0 ,2 ,3 ,
            0 ,3 ,4 ,
            0 ,4 ,5 ,
            0 ,5 ,6 ,
            0 ,6 ,1 ,
        };
       
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
        
        //Create Buffers
        void createBuffer(VkDeviceSize size,VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        //Create Uniform Buffers
        void createDescriptorSetLayout();
        void createUniformBuffers();
        void updateUniformBuffer(uint32_t currentImage);
        void createDescriptorPool();
        void createDescriptorSets();

        //Create Vertex Buffers
        void createVertexBuffer();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        //Create Index Buffers
        void createIndexBuffer();

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


