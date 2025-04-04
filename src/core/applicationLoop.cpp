#include "core.hpp"
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vulkan/vulkan_core.h>
#include <chrono>

namespace Core {
    void Application::StartLoop(){
        std::cout << "Application loop started.\n";
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        bool mouseDisabled = true;
        
        float sensitivity = 0.02f;
        

        while(!glfwWindowShouldClose(m_window)){
            glfwPollEvents();

            static auto startTime = std::chrono::high_resolution_clock::now();

            auto currentTime = std::chrono::high_resolution_clock::now();
            float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

            if(mouseDisabled){
                float xdif = m_input.GetMousePosX(*m_window) - m_swapChainExtent.width/2.0f , ydif =  m_input.GetMousePosY(*m_window) - m_swapChainExtent.height/2.0f;
                azimuth += xdif * time * sensitivity;
                altitude -= ydif * time * sensitivity;

                azimuth = std::fmod(azimuth,360.0f);
                altitude = std::clamp(altitude,5.0f,175.0f);

                glfwSetScrollCallback(m_window, scrollCallback);
            }            

            //std::cout << azimuth << ' ' << altitude << '\n';

            if(m_input.IsKeyPressed(*m_window,GLFW_KEY_ESCAPE)){
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                mouseDisabled = false;
            }
            else if(m_input.IsMouseButtonPressed(*m_window, GLFW_MOUSE_BUTTON_1)){
                glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                mouseDisabled = true;
            }

            drawFrame(); 

            glfwSetCursorPos(m_window, m_swapChainExtent.width/2.0f, m_swapChainExtent.height/2.0f);

            
        }

        vkDeviceWaitIdle(m_device)  ;
        

        std::cout << "Application Closed.\n";
    }
}
