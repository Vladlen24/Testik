#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <array>
#include <list>
#include <deque>
#include <forward_list>
#include <set>

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

std::array<int, 1000000> get_rand_ar() {
    srand(time(nullptr));
    std::array<int, 1000000> ar{};
    for (int& x : ar) {
        x = rand();
    }
    return ar;
}

std::vector<int> get_rand_v(int n) {
    srand(time(nullptr));
    std::vector<int> v(n);
    for (int& x : v) {
        x = rand();
    }
    return v;
}

std::set<int> get_rand_s(int n) {
    srand(time(nullptr));
    std::vector<int> v(n);
    std::set<int> s;
    for (int& x : v) {
        x = rand();
        s.insert(x);
    }
    return s;
}

int main()
{

    {
        int n = 2000000;
        std::vector<int> v = get_rand_v(n);
        {
            std::cout << "set: ";                                               // сложность этого блока иммет ассимптотику O(NlogN); при замерах времени
            Timer t;                                                            // была заметна зависимость времени от количества элементов в векторе как раз
                                                                                // по закону NlogN с некоторым коэффициентом (в зависимости от системы и компилятора он может
            std::set<int> s;                                                    // разнится; у меня получился 0.0001. {Пример: при 200000 элемент блок отработал за 248 милисекунд}
            for (int& x : v) {
                x = rand();
                s.insert(x);
            }
        }
        {
            std::cout << "vector sort: ";                                       // этот блок также имеет сложность O(NlogN), но уже со своим коэффициентом
            Timer t;                                                            // при сериях измерений врмени работы выяснилось что этот блок работает в 1.3 раза быстрее блока с set
                                                                                // {Пример: при 200000 элемент блок отработал за 185 милисекунд}
            srand(time(nullptr));
            std::vector<int> v1(v.size());
            for (int i = 0; i < v.size(); ++i) {
                v1.push_back(v[i]);
            }
            std::sort(std::begin(v1), std::end(v1));
        }
        {
            std::cout << "array sort: ";                                       // этот блок также имеет сложность O(NlogN), но уже со своим коэффициентом
            Timer t;                                                            // при сериях измерений врмени работы выяснилось что этот блок работает в 3.8 раза быстрее блока с set
                                                                                // {Пример: при 200000 элемент блок отработал за 63 милисекунд}
            srand(time(nullptr));
            std::array<int, 2000000> ar{};
            for (int i = 0; i < v.size(); ++i) {
                ar[i] = v[i];
            }
            std::sort(std::begin(ar), std::end(ar));
        }                                                                       // Порогового значения при котором сменяется лидер НЕ ОБНАРУЖЕНО, дошел по количеству элементов
    }                                                                           // уже до того, что памяти не хватало и программа падала, а очередность оставалась прежней


    return 0;
}