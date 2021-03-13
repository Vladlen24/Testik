#include <string>
#include <regex>
#include <boost/locale.hpp>
#include <iostream>

int main(int argc4, char ** argv4) {
    std::string data1 = "1894.12.31 23:13:59"    // true
                        "2025.12.31 23:13:59"    // false (год > 2021)
                        "0023.03.16 02:01:01"    // true
                        "0023.13.16 02:01:01"    // false (месяц > 12)
                        "1535.10.28 18:54:23"    // true
                        "1535.10.32 18:54:23"    // false (число > 31)
                        "2021.03.11 16:54:23"    // true
                        "2021.03.11 24:54:23"    // false (часов > 23)
                        "2021.03.11 16:64:23"    // false (минут > 59)
                        "2021.03.11 16:24:72";   // false (секунд > 59)

    std::regex reg1(R"((([0-1]\d{3})|(20(([0-1]\d)|(2[0-1]))))\.((0\d)|(1[0-2]))\.(([0-2]\d)|(3[0-1]))\s((?:[0-1]\d)|(2[0-3])):([0-5]\d):([0-5]\d))");

    std::sregex_iterator beg1(data1.cbegin(),data1.cend(),reg1);
    std::sregex_iterator end1;
    for_each (beg1,end1,[](const std::smatch& m1) {
        std::cout << "match:  " << m1.str() << std::endl;
    });
}