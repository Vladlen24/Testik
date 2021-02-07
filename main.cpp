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
    std::chrono::milliseconds interval_pause{100};
    Timer(): m_begin(clock_t::now()) {}
    ~Timer()
    {
        auto end = clock_t::now();
        std::cout << "milliseconds: " << std::chrono::duration_cast <std::chrono::milliseconds> (end - m_begin).count() - interval_pause.count() << std::endl;
    }
    /*void pause()
    {
        ++interval_pause;
    }*/
private:
    time_point_t m_begin;
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

    //Timer::pause();

    return 0;
}
