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
    //std::cout << "minimum: " << *min_element(v.begin(), v.end()) << std::endl;
    //std::cout << "maximum: " << *max_element(v.begin() ,v.end()) << std::endl;
    const auto [min, max] = std::minmax_element(v.begin(), v.end());
    std::cout << "min = " << *min << ", max = " << *max << std::endl;
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
//-----------------------------------------------------TASK 8-----------------------------------------------------------
    transform (v.begin(), v.end(),                                  // источник
                v.begin(),                                          // нач. знач.
                [](int x){return x*x;});                    // квадраты
    print(v, "Квадраты: ");
//-----------------------------------------------------TASK 9-----------------------------------------------------------
    std::vector<int> v2(v.size());
    //std::default_random_engine dre2;        // можно и генератором случайных чисел
    std::generate(v2.begin(), v2.end(),       // интервал
                 rand);                       // источник случайности
    print(v2, "Послед №2: ");
//-----------------------------------------------------TASK 10----------------------------------------------------------
    std::cout << "Сумма послед2: "
         << accumulate (v2.begin(), v2.end(),               // источник
                        0)                            // начальное значение
         << std::endl;
//-----------------------------------------------------TASK 11----------------------------------------------------------
    /*std::sort(v2.begin(), v2.end());               // можно сделать через replace_if, но тогда нужно сортировать
     int bound = 846930887;                          // вектор и знать точное значение границы bound (это плохо)
    replace_if (v2.begin(), v2.end(),                // range
                bind2nd(std::less<int>(), bound),    // criterion for replacement
                1);*/
    int k = 6;
    fill(v2.begin(), std::next(v2.begin(), k),            // источник
             1);                                            // новое значение
    print(v2, "Замена первых k: ");
//-----------------------------------------------------TASK 12----------------------------------------------------------
    std::vector<int> v3(v.size());
    transform(v.begin(), v.end(),               // источник 1
              v2.begin(), v3.begin(),           // источник 2
              std::minus<int>());      // операция
    print(v3, "После №3: ");
//-----------------------------------------------------TASK 13----------------------------------------------------------
    replace_if (v3.begin(), v3.end(),                        // источник
                bind2nd(std::less<int>(), 0),    // критерий замены
                0);
    print(v3, "Положит. послед3: ");
//-----------------------------------------------------TASK 14----------------------------------------------------------
    //std::sort(v3.begin(), v3.end());
    std::vector<int>::iterator pos3;
    pos3 = remove(v3.begin(), v3.end(),            // источник
                 0);                         // удаляемое значение
    v3.erase(pos3, v3.end());
    print(v3, "Послед3 без нулей: ");
//-----------------------------------------------------TASK 15----------------------------------------------------------
    std::reverse(v3.begin(), v3.end());
    print(v3, "Послед3 в обратном поряке: ");
//-----------------------------------------------------TASK 16----------------------------------------------------------
    nth_element (v3.begin(),                        // начало отсчета
                 v3.end()-3,                    // element that should be sorted correctly
                 v3.end());                         // конец отсчета
    std::cout << "Топ-3: ";
    copy (v3.end()-3, v3.end(),
          std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
//-----------------------------------------------------TASK 17----------------------------------------------------------
    std::sort(v.begin(), v.end());
    print(v, "Послед1 отсорт: ");
    std::sort(v2.begin(), v2.end());
    print(v2, "Послед2 отсорт: ");
//-----------------------------------------------------TASK 18----------------------------------------------------------
    std::vector<int> v4(2 * v.size());
    merge (v.begin(), v.end(),
           v2.begin(), v2.end(),
           v4.begin());
    print(v4, "Слияние П1 и П2: ");
//-----------------------------------------------------TASK 19----------------------------------------------------------
    std::vector<int>::iterator pos4, pos5;

    pos4 = lower_bound (v4.begin(), v4.end(),
                        1);
    pos5 = upper_bound (v4.begin(), v4.end(),
                        1);

    std::cout << "1 может быть вставлена на позицию с "
         << distance(v4.begin(), pos4) + 1
         << " по "
         << distance(v4.begin(),pos5) + 1
         << " для упорядоченой сортировки" << std::endl;
//-----------------------------------------------------TASK 20----------------------------------------------------------
    // has been doing for the whole programm:)
    print(v, "Послед №1: ");
    print(v2, "Послед №2: ");
    print(v3, "Послед №3: ");
    print(v4, "Послед №4: ");

    return 0;
}
