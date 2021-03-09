#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>

int main()
{
    std::string s1;
    std::cin >> s1;
    std::istringstream in1(s1);
    long double v1;
    in1.imbue(std::locale("en_US.UTF-8"));
    in1 >> std::get_money(v1);
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cout << std::showbase << "RUB -> USD: " << std::put_money(v1 * 73)
              << " or " << std::put_money(v1 * 73, true) << '\n';

    return 0;
}