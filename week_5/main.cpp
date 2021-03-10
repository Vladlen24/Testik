#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif

#include <map>
#include <codecvt>
#include <locale>
#include <string>
#include <boost/locale.hpp>
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

int main() {

//---------------------------------------------------------TASK №1------------------------------------------------------
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


//---------------------------------------------------------TASK №2------------------------------------------------------
// так как я раюотаю в Linux, то в консоле по умолчанию UTF-8, поэтому я не делал перевод из cp1251 в utf-8, но это вообще не сложно, так что если надо могу сделать
    //std::string a{"привет ребята, как делишки"};
    std::string str;
    std::getline(std::cin, str);

    std::u32string u32string = boost::locale::conv::utf_to_utf < char32_t, char > (str);      // перевод из UTF-8 в UTF-32

    std::map<char32_t, std::u32string> letters {{U'\u0430', U"a"}, {U'\u0431', U"b"}, {U'\u0432', U"w"}, {U'\u0433', U"g"}, {U'\u0434', U"d"}, {U'\u0435', U"e"}, {U'\u0451', U"e"}, {U'\u0436', U"j"}, {U'\u0437', U"z"}, {U'\u0438', U"i"}, {U'\u0439', U"i"}, {U'\u043A', U"k"}, {U'\u043B', U"l"}, {U'\u043C', U"m"}, {U'\u043D', U"n"}, {U'\u043E', U"o"}, {U'\u043F', U"p"}, {U'\u0440', U"r"}, {U'\u0441', U"s"}, {U'\u0442', U"t"}, {U'\u0443', U"u"}, {U'\u0444', U"f"}, {U'\u0445', U"h"}, {U'\u0446', U"c"}, {U'\u0447', U"c"}, {U'\u0448', U"s"}, {U'\u0020', U" "}, {U'\u0021', U"!"}, {U'\u002c', U","}, {U'\u044B', U"w"}, {U'\u044C', U"b"}, {U'\u044D', U"e"}, {U'\u044E', U"u"}, {U'\u044F', U"j"}};
    std::u32string newstr;                                              // новый элемент из UTF-32, в который мы будем записывать конвентированный (транслитерированый) текст
    for (auto i: u32string) {
        if (letters.find(i) != letters.end()){
             newstr.append(letters.find(i)->second);                    // заменяем символ в кириллице на соответствующий ему из таблицы символ латиницы
        }
    }

    std::string b = boost::locale::conv::utf_to_utf < char, char32_t > (newstr);            // преобразуем UTF-32 назад в UTF-8
    std::cout << b << std::endl;



    return 0;
}