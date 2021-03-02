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
bool isSimple(int a)
{
    bool f;
    int d;
    f = a <= 1;
    d = 2;
    while ((!f) && (d*d <= a)){
        if (a % d == 0){
            f = true;
        }
        else {
            d++;
        }
    }
    return !f;
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
//-----------------------------------------------------TASK 5-----------------------------------------------------------
    int numb = 0;
    numb = std::count_if(v.begin(), v.end(),
                         [](int x){return (std::abs(x) % 2) == 1;});
    std::cout << "Количество нечетных: " << numb << std::endl;
//-----------------------------------------------------TASK 6-----------------------------------------------------------
    std::cout << "minimum: " << *min_element(v.begin(), v.end()) << std::endl;
    std::cout << "maximum: " << *max_element(v.begin() ,v.end()) << std::endl;
//-----------------------------------------------------TASK 7-----------------------------------------------------------
    auto pos1 = std::find_if(v.cbegin(), v.cend(), [](int a){
        bool f;
        int d;
        f = a <= 1;
        d = 2;
        while ((!f) && (d*d <= a)){
            if (a % d == 0){
                f = true;
            }
            else {
                d++;
            }
        }
        return !f;});
    if (pos1 != v.end()) {
        std::cout << *pos1 << " - простое число" << std::endl;
    }
    else {
        std::cout << *pos1 << "Простое число не найдено" << std::endl;
    }

    return 0;
}
