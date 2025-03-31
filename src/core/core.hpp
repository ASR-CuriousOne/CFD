#ifndef CORE_H
#define CORE_H
#include <cstddef>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <cstdint>
#include <cwchar>
#include <glm/ext/scalar_uint_sized.hpp>
#include <optional>
#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
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
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;
        glm::vec3 normal;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            attributeDescriptions[3].binding = 0;
            attributeDescriptions[3].location = 3;
            attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[3].offset = offsetof(Vertex, normal);

            return attributeDescriptions;
        }
    };

    struct Mesh{
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
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

        VkImage m_textureImage;
        VkDeviceMemory m_textureImageMemory;
        VkImageView m_textureImageView;
        VkSampler m_textureSampler;

        VkImage m_depthImage;
        VkDeviceMemory m_depthImageMemory;
        VkImageView m_depthImageView;



        //Hexagon
        /*const std::vector<Vertex> m_vertices = {
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
        };*/

        //Quad
        const std::string TEXTURE_PATH = "textures/map.jpg"; 
        const float texSize = 0.25f; // 1/4th of the full texture

/*std::vector<Vertex> m_vertices = {
    // Front face (Region 0,0)
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.00f, 0.00f}},  
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {texSize, 0.00f}},  
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {texSize, texSize}},  
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.00f, texSize}},  

    // Back face (Region 1,0)
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {texSize, 0.00f}},  
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {texSize * 2, 0.00f}},  
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {texSize * 2, texSize}},  
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {texSize, texSize}},  

    // Left face (Region 2,0)
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {texSize * 2, 0.00f}},  
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {texSize * 3, 0.00f}},  
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {texSize * 3, texSize}},  
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {texSize * 2, texSize}},  

    // Right face (Region 3,0)
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {texSize * 3, 0.00f}},  
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {texSize * 4, 0.00f}},  
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {texSize * 4, texSize}},  
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {texSize * 3, texSize}},  

    // Top face (Region 0,1)
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.00f, texSize}},  
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {texSize, texSize}},  
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {texSize, texSize * 2}},  
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.00f, texSize * 2}},  

    // Bottom face (Region 1,1)
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {texSize, texSize}},  
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {texSize * 2, texSize}},  
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {texSize * 2, texSize * 2}},  
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {texSize, texSize * 2}},  
};
        std::vector<uint32_t> m_indices = {
    // Front face
    0, 1, 2,
    2, 3, 0,
    // Back face
    4, 5, 6,
    6, 7, 4,
    // Left face
    8, 9, 10,
    10, 11, 8,
    // Right face
    12, 13, 14,
    14, 15, 12,
    // Top face
    16, 17, 18,
    18, 19, 16,
    // Bottom face
    20, 21, 22,
    22, 23, 20
};*/

        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;

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
        VkImageView createImageViewForImage(VkImage image, VkFormat format,VkImageAspectFlags aspectFlag);

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

        //Mesh Work
        void loadModel();

        //Create Vertex Buffers
        void createVertexBuffer();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        //Create Index Buffers
        void createIndexBuffer();

        //Create Command Buffer
        void createCommandPool();
        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        //create Texture Image
        void createTextureImage();     
        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);    
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        void createTextureImageView();
        void createTextureSampler();

        //create Depth Buffer
        void createDepthResources();
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);    
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);

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


