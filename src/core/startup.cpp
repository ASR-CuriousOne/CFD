#include <iostream>
#include <string>

namespace Core{

    int StartLoop();

    int InitializeApplication(){
        std::cout << "Application Started" << '\n';

        return StartLoop();
    }

    int StartLoop(){
        while(true){
            std::cout << "This is an Application.\nPress Y to continue.\nPress N to exit.";
            std::string s;
            std::cin >> s;
            
            if(s == "N"){
                std::cout << "Bye Bye \\-_-/ \n";
                break;
            }
        }
    }
}