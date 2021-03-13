#include <string>
#include <regex>
#include <boost/locale.hpp>
#include <iostream>

int main(int argc3, char ** argv3) {
    std::string data = "dssf23./7 vladlen24@gmail.com frgg/f34.f7_f dssf23./7 statev@phystech.edu frgg/f34.f7_f ponchik@makaronchik.www.fgfh";

    std::regex reg(R"((\w+)@(\w+)\.(\w+))");

    std::sregex_iterator beg(data.cbegin(),data.cend(),reg);
    std::sregex_iterator end;
    for_each (beg,end,[](const std::smatch& m) {
        std::cout << "match:  " << m.str() << std::endl;
        std::cout << " name:   " << m.str(1) << std::endl;
        std::cout << " domen: " << m.str(2) << "." << m.str(3) << std::endl;
    });
}