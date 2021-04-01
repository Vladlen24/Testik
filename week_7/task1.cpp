#include <iostream>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>
#include <numeric>
#include <atomic>
#include <cstdint>
#include <future>

static constexpr size_t NUMBER = 8;
static constexpr size_t THREAD_ITTERS = 40000000;

class Timer
{
public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;

    Timer(): m_begin(clock_t::now()) {}

    ~Timer()
    {
        auto end = clock_t::now();
        std::cout << std::chrono::duration_cast <std::chrono::milliseconds>(end - m_begin).count() << " milliseconds" << std::endl;

    }

private:
    time_point_t m_begin;
};

int rrand(int range_min, int range_max) {
    return rand() % (range_max - range_min + 1) + range_min;
}

double MonteCarlo(size_t iters) {

    srand((unsigned) time(0));

    unsigned cnt = 0;
    unsigned side = 1000;
    unsigned qside = side * side;

    for (int i = 0; i < iters; ++i) {
        unsigned x = rrand(0, side);
        unsigned y = rrand(0, side);

        if ((x * x + y * y) < qside) ++cnt;
    }

    return double(cnt) / iters * 4;
}

int main() {

    //паралельная версия через vector<future<>> ООООЧЕНЬ МЕДЛЕННО
    {
        std::cout << "Threads (vector)" << std::endl;
        Timer t;
        std::vector<double> result;
        std::vector<std::future<double>> fus;
        for (int i = 0; i < NUMBER; ++i) {
            size_t cnt = THREAD_ITTERS;
            fus.emplace_back(std::async(MonteCarlo, cnt));
        }
        result.reserve(fus.size());
        for (auto& fu: fus) {
            result.emplace_back(fu.get());
        }
        std::cout << std::accumulate(result.begin(), result.end(),0.0) / result.size() << std::endl;
    }

    //паралельная версия просто через future и async     НОРМ ПО СКОРОСТИ
    {
        std::cout << "Threads" << std::endl;
        Timer t;
        std::vector<double> result;
        for (int i = 0; i < NUMBER; ++i) {
            size_t cnt = THREAD_ITTERS;
            std::future<double> fu = std::async(MonteCarlo, cnt);
            result.emplace_back(fu.get());
        }
        std::cout << std::accumulate(result.begin(), result.end(),0.0) / result.size() << std::endl;
    }

    //последовательная версия
    {
        std::cout << "Iterative" << std::endl;
        Timer t;
        std::cout << MonteCarlo(THREAD_ITTERS * NUMBER) << std::endl;
    }

    //после написания через async и future скорости работы последовательной и итеративной уравнялись с точностью до 0.5%

    //как оказалось версия через вектор фьючеров очень медленная

    return 0;
}