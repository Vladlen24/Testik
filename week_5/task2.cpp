#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif

#include <map>
#include <string>
#include <boost/locale.hpp>
#include <iostream>

int main(int argc2, char ** argv2) {
// так как я раюотаю в Linux, то в консоле по умолчанию UTF-8, поэтому я не делал перевод из cp1251 в utf-8, но это вообще не сложно, так что если надо могу сделать
//std::string a{"привет ребята, как делишки"};
    std::string str;
    std::getline(std::cin, str);

    std::u32string u32string = boost::locale::conv::utf_to_utf<char32_t, char>(str);      // перевод из UTF-8 в UTF-32

    std::map<char32_t, std::u32string> letters{{U'\u0430', U"a"},
                                               {U'\u0431', U"b"},
                                               {U'\u0432', U"w"},
                                               {U'\u0433', U"g"},
                                               {U'\u0434', U"d"},
                                               {U'\u0435', U"e"},
                                               {U'\u0451', U"e"},
                                               {U'\u0436', U"j"},
                                               {U'\u0437', U"z"},
                                               {U'\u0438', U"i"},
                                               {U'\u0439', U"i"},
                                               {U'\u043A', U"k"},
                                               {U'\u043B', U"l"},
                                               {U'\u043C', U"m"},
                                               {U'\u043D', U"n"},
                                               {U'\u043E', U"o"},
                                               {U'\u043F', U"p"},
                                               {U'\u0440', U"r"},
                                               {U'\u0441', U"s"},
                                               {U'\u0442', U"t"},
                                               {U'\u0443', U"u"},
                                               {U'\u0444', U"f"},
                                               {U'\u0445', U"h"},
                                               {U'\u0446', U"c"},
                                               {U'\u0447', U"c"},
                                               {U'\u0448', U"s"},
                                               {U'\u0020', U" "},
                                               {U'\u0021', U"!"},
                                               {U'\u002c', U","},
                                               {U'\u044B', U"w"},
                                               {U'\u044C', U"b"},
                                               {U'\u044D', U"e"},
                                               {U'\u044E', U"u"},
                                               {U'\u044F', U"j"}};
    std::u32string newstr;                                              // новый элемент из UTF-32, в который мы будем записывать конвентированный (транслитерированый) текст
    for (auto i: u32string) {
        if (letters.find(i) != letters.end()) {
            newstr.append(letters.find(i)->second);                    // заменяем символ в кириллице на соответствующий ему из таблицы символ латиницы
        }
    }

    std::string b = boost::locale::conv::utf_to_utf<char, char32_t>(newstr);            // преобразуем UTF-32 назад в UTF-8
    std::cout << b << std::endl;

}