#include <iostream>
#include <fstream>

int main(){
    const std::string& filename = "test2.txt";

    std::ifstream file(filename);

    std::string s;
    getline(file, s, '\n');
    int str_size = s.size() + 1;
    int n;
    std::cin >> n;
    file.seekg((n-1)*str_size);
    std::string str(str_size, '\n');
    if(file.read(&str[0], str_size))
            std::cout << str << '\n';

    return 0;
}