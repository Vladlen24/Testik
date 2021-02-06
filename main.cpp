#include <iostream>
#include <cmath>

int multiply(int a, int b) {

    return a * b;
}

void f() {}

int main()
{
    int a{7}, b{6};
    std::cout << "Hello, world!";
    std::cout << pow(a, b) << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << multiply(a, b) << std::endl;
    return 0;
}
