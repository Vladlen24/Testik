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
static constexpr size_t THREAD_ITTERS = 400000;

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

    {
        std::cout << "Threads (vector)" << std::endl;
        Timer t;
        std::vector<double> result;
        std::vector<std::thread> fus;
        std::mutex m;
        for (int i = 0; i < NUMBER; ++i) {
            size_t cnt = THREAD_ITTERS;
            fus.emplace_back([&result, &m, cnt]() {
                double pi = MonteCarlo(cnt);
                std::lock_guard<std::mutex> lk(m);
                result.emplace_back(pi);
            });
        }
        for (auto& th : fus) {
            th.join();
        }
        std::cout << std::accumulate(result.begin(), result.end(),0.0) / result.size() << std::endl;
    }

    return 0;
}