#include <iostream>
#include <list>
#include <numeric>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

void print (std::vector<int> &v, std::string s) {
    std::cout << s;
    copy(v.cbegin(), v.cend(),
         std::ostream_iterator<int> (std::cout, " "));
    std::cout << std::endl;
}

int main() {
//-----------------------------------------------------TASK 1-----------------------------------------------------------
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);
    print(v, "Последов: ");
//-----------------------------------------------------TASK 2-----------------------------------------------------------
    copy(std::istream_iterator<int> (std::cin), std::istream_iterator<int> (),
            back_inserter(v));
    print(v, "Вставка: ");
//-----------------------------------------------------TASK 3-----------------------------------------------------------
    std::default_random_engine dre;        // генератор случайных чисел по умолчанию
    std::shuffle(v.begin(), v.end(),       // интервал
                 dre);                     // источник случайности
    print(v, "Перетасовка: ");
//-----------------------------------------------------TASK 4-----------------------------------------------------------
    std::sort(v.begin(), v.end());
    std::vector<int>::iterator pos;
    pos = std::unique(v.begin(), v.end());
    v.erase(pos, v.end());
    print(v, "Без дубликатов: ");
    std::cout << std::endl;

    return 0;
}
