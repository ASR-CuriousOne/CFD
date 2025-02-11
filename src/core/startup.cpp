#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include <vulkan/vulkan_core.h>
#include "core.hpp"

#define HEIGHT 600
#define WIDTH 800

namespace Core{
        
        Application::Application(){
            std::cout << "Initializing Application.......\n";
            InitializeWindow();
            InitializeVulkan();
            std::cout << "Application Initilized" << '\n';
            StartLoop();
            CleanUp();
        }

        void Application::InitializeWindow(){
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);

            m_window = glfwCreateWindow(WIDTH,HEIGHT,"Vulkan",nullptr,nullptr);
        }

        void Application::createInstance(){
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "HelloTriangle";
            appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;
            
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;

            createInfo.enabledLayerCount = 0;

            if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS){
                throw std::runtime_error("failed to create instance!");
            }
        }

        void Application::InitializeVulkan(){
            createInstance();
        }
         

        void Application::StartLoop(){
            std::cout << "Application loop started.\n";
            while(!glfwWindowShouldClose(m_window)){
                glfwPollEvents();
            
             }
            std::cout << "Application Closed.\n";
        }
            
        void Application::CleanUp(){
            std::cout << "Cleaning Up.......\n";
            vkDestroyInstance(m_vkInstance, nullptr);
            glfwDestroyWindow(m_window);
            glfwTerminate();
            std::cout << "Cleaned.\n";
        }

          
    
}
