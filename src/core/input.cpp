#include "input.hpp"

#include <GLFW/glfw3.h>
#include <utility>

namespace Core {
    bool Input::IsKeyPressed(GLFWwindow& window, int keyCode){
        auto state = glfwGetKey(&window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(GLFWwindow& window, int button){
        auto state = glfwGetMouseButton(&window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePos(GLFWwindow& window){
        double xpos,ypos;
        glfwGetCursorPos(&window,&xpos,&ypos);
        return {(float)xpos,(float)ypos};
    }
    
    float Input::GetMousePosX(GLFWwindow& window){
        auto[xpos,_] = GetMousePos(window);
        return (float)xpos;
    }

    float Input::GetMousePosY(GLFWwindow& window){
        auto[_,ypos] = GetMousePos(window);
        return (float)ypos;
    }
} 
