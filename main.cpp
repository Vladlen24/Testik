#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <algorithm>

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
    inline static time_point_t beg_pause = clock_t::now();
    inline static time_point_t end_pause = clock_t::now();
    Timer(): m_begin(clock_t::now()) {}
    ~Timer()
    {
        auto end = clock_t::now();
        std::cout << "milliseconds (whole program): " << std::chrono::duration_cast <std::chrono::milliseconds> (end - m_begin).count() << std::endl;
        std::cout << "pause begin: " << std::chrono::duration_cast <std::chrono::milliseconds> (beg_pause - m_begin).count() << std::endl;
        std::cout << "pause end: " << std::chrono::duration_cast <std::chrono::milliseconds> (end_pause - m_begin).count() << std::endl;
        std::cout << "milliseconds (with pause): " << std::chrono::duration_cast <std::chrono::milliseconds> (end - m_begin).count() -
                                         std::chrono::duration_cast <std::chrono::milliseconds> (end_pause - beg_pause).count() << std::endl;
    }
    static void pause()
    {
        beg_pause = clock_t::now();
    }
    static void pusk()
    {
        end_pause = clock_t::now();
    }
private:
    time_point_t m_begin;
    std::chrono::milliseconds interval_pause;
    std::chrono::milliseconds interval2;
};

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

    std::vector v (1000000, 0);

    for (auto i = 0; i < std::size(v); ++i)
    {
        v[i] = 1000000 - i;
    }

    Timer t;
    std::sort(std::begin(v), std::end(v));

    Timer::pause();

    std::sort(std::begin(v), std::end(v));

    Timer::pusk();

    std::sort(std::begin(v), std::end(v));

    return 0;
}
