#include "core.hpp"
#include <iostream>

namespace Core {
    void Application::StartLoop(){
        std::cout << "Application loop started.\n";
        while(!glfwWindowShouldClose(m_window)){
            glfwPollEvents();
            drawFrame(); 


         }
        vkDeviceWaitIdle(m_device);

        std::cout << "Application Closed.\n";
    }
}
