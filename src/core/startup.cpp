#include <GLFW/glfw3.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan_core.h>
#include "core.hpp"

#define HEIGHT 600
#define WIDTH 800

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData) {

            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

            return VK_FALSE;
    }


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

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = &debugCreateInfo;
        } 
        else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }


        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
    
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        
 
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
    
        if (vkCreateInstance(&createInfo, nullptr, &m_vkInstance) != VK_SUCCESS){
            throw std::runtime_error("failed to create instance!");
        }
    }
    
    void Application::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
    }


    void Application::setupDebugMessenger(){
        if (!enableValidationLayers) return;
        
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        populateDebugMessengerCreateInfo(createInfo);
        

        if (Application::CreateDebugUtilsMessengerEXT(m_vkInstance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    VkResult Application::CreateDebugUtilsMessengerEXT(
            VkInstance instance, 
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
            const VkAllocationCallbacks* pAllocator, 
            VkDebugUtilsMessengerEXT* pDebugMessenger) 
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } 
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }   

    bool Application::checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    

    std::vector<const char*> Application::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }



    void Application::InitializeVulkan(){
        createInstance();
        setupDebugMessenger();
        pickPhysicalDevice();  
        createLogicalDevice();
    }

    //Pick Physical Devices
    void Application::pickPhysicalDevice(){
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, nullptr); 
        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_vkInstance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                m_physicalDevice = device;
                break;
            }
        }

        if (m_physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    bool Application::isDeviceSuitable(VkPhysicalDevice device){
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        QueueFamilyIndices indices = findQueueFamilies(device);


        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && indices.isComplete();
    }
    
    QueueFamilyIndices Application::findQueueFamilies(VkPhysicalDevice device){
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device,&queueFamilyCount,nullptr);

        std::vector<VkQueueFamilyProperties> allQueueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device,&queueFamilyCount,allQueueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : allQueueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            i++;
        }

        return indices;

    }

    //Make Logical Devices
    void Application::createLogicalDevice(){
        QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);
        
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        float queueFamilyPriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queueFamilyPriority;

        VkPhysicalDeviceFeatures deviceFeatures{};
        
        VkDeviceCreateInfo deviceCreateInfo{};

        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;
        deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
        deviceCreateInfo.enabledExtensionCount = 0;

        if(enableValidationLayers){
            deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
        }
        else{
            deviceCreateInfo.enabledLayerCount = 0;
        }

        if(vkCreateDevice(m_physicalDevice,&deviceCreateInfo,nullptr,&m_device) != VK_SUCCESS){
            throw std::runtime_error("failde to create logical device");
        }

        vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
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
        vkDestroyDevice(m_device, nullptr);
        if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(m_vkInstance, m_debugMessenger, nullptr);
        }
        vkDestroyInstance(m_vkInstance, nullptr);
        glfwDestroyWindow(m_window);
        glfwTerminate();
        std::cout << "Cleaned.\n";
    }

    void Application::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT m_debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, m_debugMessenger, pAllocator);
    }
}

          
    
}
