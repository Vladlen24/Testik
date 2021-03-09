#include <iomanip>
#include <iostream>

const long double KOEF{73};             // коэффициент перевода доллара в рубли

int main()
{
    long double v1;
    std::cin.imbue(std::locale("en_US.UTF-8"));                                         // конвертация долларов в рубли
    std::cin >> std::get_money(v1,false);
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cout << std::showbase << "USD -> RUB: " << std::put_money(v1 * KOEF)
              << " or " << std::put_money(v1 * KOEF, true) << '\n';

    long double v2;
    std::cin.imbue(std::locale("ru_RU.UTF-8"));                                         // конвертация рублей в доллары
    std::cin >> std::get_money(v2, false);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::showbase << "RUB -> USD: " << std::put_money(v2 / KOEF)
              << " or " << std::put_money(v2 / KOEF, true) << '\n';


    return 0;
}