#ifndef INPUT_HPP
#define INPUT_HPP
#include <GLFW/glfw3.h>
#include <utility>

namespace Core {
    
    class Input{
        public:
            bool IsKeyPressed(GLFWwindow& window,int keyCode);

            bool IsMouseButtonPressed(GLFWwindow& window,int button);
            std::pair<float, float> GetMousePos(GLFWwindow& window);
            float GetMousePosX(GLFWwindow& window);
            float GetMousePosY(GLFWwindow& window);

        private:
             
    };

}

#endif
