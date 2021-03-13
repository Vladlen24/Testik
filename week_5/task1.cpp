#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif

#include <codecvt>
#include <locale>
#include <string>
#include <iomanip>
#include <iostream>

const long double KOEF{73};             // коэффициент перевода доллара в рубли

bool is_little_endian_system()
{
    char16_t test = 0x0102;
    return (reinterpret_cast < char * > (&test))[0] == 0x02;
}

std::u16string convert_utf8_to_utf16(const std::string & string)
{
    static bool little_endian_system = is_little_endian_system();

    if (little_endian_system)
    {
        std::wstring_convert < std::codecvt_utf8_utf16 <
                char16_t, 0x10ffffU, std::codecvt_mode::little_endian > , char16_t > converter;
        return converter.from_bytes(string);
    }
    else
    {
        std::wstring_convert < std::codecvt_utf8_utf16 < char16_t > , char16_t > converter;
        return converter.from_bytes(string);
    }

}

int main(int argc1, char ** argv1) {
    long double v1;
    std::cin.imbue(std::locale("en_US.UTF-8"));                                         // конвертация долларов в рубли
    std::cin >> std::get_money(v1, false);
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cout << std::showbase << "USD -> RUB: " << std::put_money(v1 * KOEF)
              << " or " << std::put_money(v1 * KOEF, true) << '\n';

    long double v2;
    std::cin.imbue(std::locale("ru_RU.UTF-8"));                                         // конвертация рублей в доллары
    std::cin >> std::get_money(v2, false);
    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::showbase << "RUB -> USD: " << std::put_money(v2 / KOEF)
              << " or " << std::put_money(v2 / KOEF, true) << '\n';
}