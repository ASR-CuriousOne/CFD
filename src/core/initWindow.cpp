#include "core.hpp"
#include <stdexcept>

#define HEIGHT 800
#define WIDTH 800

namespace Core {
    void Application::InitializeWindow(){
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
    
        m_window = glfwCreateWindow(WIDTH,HEIGHT,"Vulkan",nullptr,nullptr);
        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
    }

    void Application::createSurface(){
        if (glfwCreateWindowSurface(m_vkInstance, m_window, nullptr, &m_surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }
}
