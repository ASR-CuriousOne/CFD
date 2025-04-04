#include "core.hpp"
#include <iostream>

namespace Core{

    Application::Application(){
        std::cout << "Initializing Application.......\n";
        InitializeWindow();
        InitializeVulkan();
        std::cout << "Application Initilized" << '\n';
        StartLoop();
    }


    Application::~Application(){
        std::cout << "Cleaning Up.......\n";
        
        cleanUpSwapChain();

        vkDestroySampler(m_device, m_NormalMapSampler, nullptr);
        vkDestroyImageView(m_device, m_NormalMapImageView, nullptr);

        vkDestroyImage(m_device, m_NormalMap, nullptr);
        vkFreeMemory(m_device, m_NormalMapMemory, nullptr);
        
        vkDestroySampler(m_device, m_textureSampler, nullptr);
        vkDestroyImageView(m_device, m_textureImageView, nullptr);

        vkDestroyImage(m_device, m_textureImage, nullptr);
        vkFreeMemory(m_device, m_textureImageMemory, nullptr);

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroyBuffer(m_device, m_uniformBuffers[i], nullptr);
            vkFreeMemory(m_device, m_uniformBuffersMemory[i], nullptr);
        }
        vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);

        vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);

        vkDestroyBuffer(m_device, m_indexBuffer, nullptr);
        vkFreeMemory(m_device, m_indexBufferMemory, nullptr);


        vkDestroyBuffer(m_device, m_vertexBuffer, nullptr);
        vkFreeMemory(m_device, m_vertexBufferMemory, nullptr);


        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            vkDestroySemaphore(m_device, m_imageAvailableSemaphores[i], nullptr);
            vkDestroySemaphore(m_device, m_renderFinishedSemaphores[i], nullptr);
            vkDestroyFence(m_device, m_inFlightFences[i], nullptr);
        }
        vkDestroyCommandPool(m_device, m_commandPool, nullptr);
       
        vkDestroyPipeline(m_device, m_graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
        vkDestroyRenderPass(m_device, m_renderPass, nullptr);

        vkDestroySurfaceKHR(m_vkInstance, m_surface, nullptr);
        vkDestroyDevice(m_device, nullptr);
        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(m_vkInstance, m_debugMessenger, nullptr);
        }
        vkDestroyInstance(m_vkInstance, nullptr);
        glfwDestroyWindow(m_window);
        glfwTerminate();
        std::cout << "Cleaned.\n";
    }
}
