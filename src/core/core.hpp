#ifndef CORE_H
#define CORE_H

#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Core{
    class Application{
       GLFWwindow* m_window;
       VkInstance m_vkInstance;

        public:
       Application();

       void Initialize();

       void InitializeWindow();

       void createInstance();

       void InitializeVulkan();

       void StartLoop();

       void CleanUp();
    };
}
#endif


