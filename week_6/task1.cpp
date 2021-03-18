#include <iostream>
#include <fstream>
#include <regex>

int main(){
    const std::string& filename = "file.txt";
    std::fstream fin(filename, std::ios::in);
    std::string text((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    std::cout << text << std::endl;

    std::string s;
    std::regex reg(R"(((\/\*)([\s\S]*?)(\*\/))|((\/\/)(.*)))");
    //std::regex_replace(std::ostreambuf_iterator<char>(std::cout), text.begin(), text.end(), reg, "");
    s = std::regex_replace(text, reg, "");

    std::ofstream file(filename);
    file << s;

    return 0;
}