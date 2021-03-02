#include <iostream>
#include <list>
#include <numeric>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

int main() {

    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);

    //std::vector<std::string> s = {"a", "b", "c", "d"};

    copy(v.cbegin(), v.cend(),
         std::ostream_iterator<int> (std::cout, " "));

    copy(std::istream_iterator<int> (std::cin), std::istream_iterator<int> (),
            back_inserter(v));

    // ПЕРЕТАСОВКА

    std::default_random_engine dre;        // генератор случайных чисел по умолчанию
    std::shuffle(v.begin(), v.end(),       // интервал
                 dre);                     // источник случайности

    copy(v.cbegin(), v.cend(),
         std::ostream_iterator<int> (std::cout, " "));
    std::cout << std::endl;

    return 0;
}
