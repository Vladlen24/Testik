#include <iostream>
#include <thread>

int main()
{
    std::thread first ([](){
        std::cout << "P" << "i" << "n" << "g" << std::endl;
    });
    std::thread second ([](){
        std::cout << "P" << "o" << "n" << "g" << std::endl;
    });

    first.join();
    second.join();

    std::string value;
    bool f = true;
    while (f){
        std::cin >> value;
        if (value == "exit") {
            f = false;
        }
        else {
            std::cout << "work" << std::endl;
        }
    }

    return 0;
}