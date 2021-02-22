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

std::vector<int> get_rand_v(int n) {
    srand(time(nullptr));
    std::vector<int> v(n);
    for (int& x : v) {
        x = rand();
    }
    return v;
}

uint64_t hash_for_double(double x) {                                            // хэш-функция для double. Принцип работы переводит 64 бита (8 байтов), которые представляют
                                                                                // число типа double, в такие же 8 байт только теперь описывающие уже тип int. То есть байты
    void* temp = &x;                                                            // одни и те же, но в памяти представляются по-разному
    auto* cast = static_cast<uint64_t *>(temp);
    auto hash = *cast;

    return hash;
}

uint32_t hash_for_float(float x) {                                              // хэш-функция для float. Идея и реализация абсолютно такая же, только тут уже 32 бита (4 байта)
                                                                                // За счет принципа работы этой хэш-функции получается, что она устанавливает взаимно однозначное
    void* temp = &x;                                                            // соответствие (биекцию) между аргументом и результатом. Поэтому можно считать эту хэш-функцию
    auto* cast = static_cast<uint32_t *>(temp);                                 // ИДЕАЛЬНОЙ (коллизии отсутствуют). Конечно в учет не брался тот факт, что при превышении допустимой
    auto hash = *cast;                                                          // точности соответствующего типа хэш-код будет одинаковым. Но тут уже ничего не поделаешь(

    return hash;
}

int main()
{

    {
        int n = 10000;
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
            std::array<int, 10000> ar{};
            for (int i = 0; i < v.size(); ++i) {
                ar[i] = v[i];
            }
            std::sort(std::begin(ar), std::end(ar));
        }                                                                       // Порогового значения при котором сменяется лидер НЕ ОБНАРУЖЕНО, дошел по количеству элементов
    }                                                                           // уже до того, что памяти не хватало и программа падала, а очередность оставалась прежней

    double x = 5.7;
    std::cout << hash_for_double(x) << std::endl;                               // результат 4618103647896390861

    float y = 5.7;
    std::cout << hash_for_float(y) << std::endl;                                // результат 1085695590

    return 0;
}