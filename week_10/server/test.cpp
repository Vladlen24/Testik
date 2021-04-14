#include <iostream>
#include <cstring>

int main ()
{
    std::string s;
    std::cin >> s;
    char str[100];
    strcpy(str, s.c_str());
    std::string name = strtok (str,":!");
    std::string message = strtok (NULL, ":!");
    std::cout << name << " -- " << message;
    return 0;
}