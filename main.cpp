#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

/*int multiply(int a, int b) {

    return a * b;
}

int divide(int a, int b) {

    return a / b;
}

void f() {}
*/

class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;
    time_point_t beg_pause = clock_t::now();
    time_point_t end_pause = clock_t::now();
    std::chrono::milliseconds interval_pause{0};

    Timer(): m_begin(clock_t::now()) {}

    ~Timer()
    {
        auto end = clock_t::now();
        std::cout << "milliseconds (whole program): " << std::chrono::duration_cast <std::chrono::milliseconds>                 // время работы всех сортировок (даже тех что в паузе)
                (end - m_begin).count() << std::endl;
        std::cout << "interval of break: " << interval_pause.count() << std::endl;                                              // сумарное время всех перерывов
        std::cout << "milliseconds (only working part of program): " << std::chrono::duration_cast <std::chrono::milliseconds>
                (end - m_begin).count() - interval_pause.count() << std::endl;                                               // время работы только "активных" сортировок
    }

    void pause()
    {
        beg_pause = clock_t::now();
    }

    void pusk()
    {
        end_pause = clock_t::now();
        interval_pause.operator+=(std::chrono::duration_cast <std::chrono::milliseconds> (end_pause - beg_pause));
    }

private:
    time_point_t m_begin;
};

std::vector<int> get_rand_v(int n) {
    srand(time(nullptr));
    std::vector<int> v(n);
    for (int& x : v) {
        x = rand();
    }
    return v;
}

int main()
{
    /*int a{7}, b{6};
    std::cout << "Hello, master";
    std::cout << pow(a, b) << std::endl;
    std::cout << std::sqrt(pow(a,2) + pow(b,2)) << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    --a;
    ++b;
    std::cout << multiply(a, b) << std::endl;*/

    //при использовании Merge мы подгружали всю историю коммитов. Благодаря этому сохраняется детальное описание
    //всех действий, но если коммитов в ветке было сделано сильно много (или паралельно в нескольких ветках работают
    //несколько разработчиков), то Log нагромаждается. Для простоты и чистоты Loga вместо Merge используем Rebase.
    //Тогда в Loge видим только одну петельку, которая отображает перемещение из новой ветки в ветку мастера (даже
    //если в новой ветке много комитов). Причем эта петелька поднимается выше последнего коммита

    std::vector<int> v = get_rand_v(1000000);

    Timer t;                                               // СТАРТ хронометра

    std::sort(std::begin(v), std::end(v));                // сортировка     (начало цикла 1)

    t.pause();                                             // ПАУЗА

    v = get_rand_v(1000000);                                 // перетасовка

    t.pusk();                                             // ПУСК

    std::sort(std::begin(v), std::end(v));               // сортировка      (конец цикла 1 && начало цикла 2)

    t.pause();                                            // ПАУЗА

    v = get_rand_v(1000000);                                // перетасовка

    t.pusk();                                             // ПУСК

    std::sort(std::begin(v), std::end(v));              // сортировка       (конец цикла 2 && начало цикла 3)

    t.pause();                                            // ПАУЗА

    v = get_rand_v(1000000);                               // перетасовка

    t.pusk();                                             // ПУСК

    std::sort(std::begin(v), std::end(v));             // сортировка       (конец цикла 3)

                                                         // ФИНИШ хронометра
    return 0;
}
