#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

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

template<typename Iterator, typename T>
struct accumulate_block{
    void operator () (Iterator first, Iterator last, T& result) {
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate (Iterator first, Iterator last, T init){

    unsigned long const length = std::distance(first, last);
    if (!length) {
        return init;
    }

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = ( length + min_per_thread - 1 ) / min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min ( hardware_threads != 0 ? hardware_threads : 2, max_threads );
    unsigned long const block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads);
    Iterator block_start = first;
    for (unsigned long i = 0; i < num_threads; ++i){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread (accumulate_block <Iterator, T> (), block_start, block_end, std::ref(results[i]) );
        block_start = block_end;
    }
    std::for_each (threads.begin(), threads.end(), std::mem_fn (&std::thread::join));
    return std::accumulate (results.begin(), results.end(), init);
}

//parallel_accumulate не мое собственное решение, а взято из справочного пособия по паралельным алгоритмам
//но разница реально очень большая
//этот код отработал на 10^9 элементов за 2 секунды, причем запустив при этом 12 потоков
//на 12 ядрах или потоках компа (как это правильно назвать) и все они одновремнно отработали на 100% (это видно на скриншотах)
//в исходном варианте запустив на таакое же количесво элементов, работали один поток на 100% и еще пару процентов на 20%
//пару секунд, пока комп просто не завис и пришлось принудительно завершить программу

int main(int argc, char ** argv)
{
    std::vector < int > v(10000);

    std::iota(v.begin(), v.end(), 1);

    Timer t;
    std::cout << parallel_accumulate(v.begin(), v.end(), 0) << std::endl;

    return EXIT_SUCCESS;
}

//(10^6,3), (5*10^6 ,16), (10*10^6,24), (15*10^6,36), (20*10^6,46), (50*10^6,148), (100*10^6,234),
//(150*10^6,359), (200*10^6,526), (500*10^6,1157), (1000*10^6,2325)
//построив график видно что зависимость времени выполнения программы линейно зависит от колиества элементов в векторе
//график прилагается