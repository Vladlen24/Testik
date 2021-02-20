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

std::deque<int> get_rand_d(int n) {
    srand(time(nullptr));
    std::deque<int> d(n);
    for (int& x : d) {
        x = rand();
    }
    return d;
}

std::list<int> get_rand_l(int n) {
    srand(time(nullptr));
    std::list<int> l(n);
    for (int& x : l) {
        x = rand();
    }
    return l;
}

std::forward_list<int> get_rand_fl(int n) {
    srand(time(nullptr));
    std::forward_list<int> fl(n);
    for (int& x : fl) {
        x = rand();
    }
    return fl;
}

void printcap(std::vector<int> &p) {
    std::cout << "size: " << p.size() << " cap: " << p.capacity() << std::endl;
}

int main()
{

    int a = 7;

    {
        std::array<int,1000000> ar = get_rand_ar();                                 // блок для МАССИВа
        std::cout << "std::sort for ARRAY: ";
        {
            Timer t1;                                                               // запускаем таймер

            std::sort(std::begin(ar), std::end(ar));                         // стандартная сортировка std::sort
        }                                                                          // конец работы таймера
        std::cout << "ar.sort() is absent for array" << std::endl;
        {
            //Timer t1;
            //ar.sort();                                                           // для массива функции-члена сортировки нет
        }
    }


    {
        std::vector<int> v = get_rand_v(1000000);                               // блок для ВЕКТОРа
        std::cout << "std::sort for VECTOR: ";
        {
            Timer t2;                                                              // запускаем таймер

            std::sort(std::begin(v), std::end(v));                          // стандартная сортировка std::sort
        }                                                                          // конец работы таймера
        std::cout << "v.sort() is absent for vector" << std::endl;
        {
            //Timer t2;
            //v.sort();                                                            // для вектора функции-члена сортировки нет
        }
    }

    {
        std::deque<int> d = get_rand_d(1000000);                                 // блок для ОЧЕРЕДи
        std::cout << "std::sort for DEQUE: ";
        {
            Timer t3;                                                               // запускаем таймер

            std::sort(std::begin(d), std::end(d));                           // стандартная сортировка std::sort
        }                                                                          // конец работы таймера
        std::cout << "d.sort() is absent for deque" << std::endl;
        {
            //Timer t3;
            //d.sort();                                                            // для очереди функции-члена сортировки нет
        }
    }

    {
        std::list<int> l = get_rand_l(1000000);                               // блок для 2-связного СПИСКа
        std::cout << "std::sort is absent for list" << std::endl;
        {
            //Timer t4;
            //std::sort(std::begin(l), std::end(l));                             // с list стандартная сортировка std::sort не работает
        }
        std::cout << "l.sort() for LIST: ";
        {
            Timer t4;                                                            // запускаем таймер
            l.sort();                                                            // функция-член сортировки у lista
        }                                                                        // конец работы таймера
    }

    {
        std::forward_list<int> fl = get_rand_fl(1000000);                       // блок для 1-связного СПИСКа
        std::cout << "std::sort is absent for forward_list" << std::endl;
        {
            //Timer t5;
            //std::sort(std::begin(fl), std::end(fl));                            // с forward_list стандартная сортировка std::sort не работает
        }
        std::cout << "fl.sort() for FORWARD_LIST: ";
        {
            Timer t5;                                                             // запускаем таймер
            fl.sort();                                                            // функция-член сортировки у forward_lista
        }                                                                         // конец работы таймера
    }


    //ИТОГ:
    //1-ый - ARRAY
    //2-ый - VECTOR
    //3-ый - DEQUE
    //4-ый - LIST
    //5-ый - FORWARD_LIST

    std::vector<int> p(1000);
    printcap(p);

    //p.push_back(3);                                    // количество дополнительно выделяемого объема (на запас) зависит от конкретного компилятора
    //printcap(p);                                    // поигравшись со своим компилятором я выяснил, что он выделяет дополнительного объема ровно столько, сколько было до этого
                                                       // То есть новый объем в 2 раза больше предыдущего (+100%)

    //std::vector<int> p1(std::pow(10,2000000));
    //printcap(p1);

    p.resize(2001);                             // Если новый размер <= старого объема, то объем остается прежнимя; если старый объем < новый размер <= 2 * (старый объем), то
    printcap(p);                                     // новый объем в 2 раза больше предыдущего, и если новый размер (size) > 2 * (старый объем), то новый объем = новому размеру

    std::vector<int> p2;                                // Если мы изначално зарезервировали какой-то объем памяти (например, 7), а потом добавляем в вектор 12 элементов, то
    p2.reserve(4);                                   // с каждым добавлением объем будем увелииваться до необхимого размера (без запаса), а если после добавлениея элементов
    p2 = {0, 1, 2, 3, 4};                               // еще сделать resize и при этом старый объем < новый size < 2 * (старый объем), то новый объем в 2 раза больше. То есть
    p2.resize(6);                               // в этом случае опять получаем тоже что и без reserve
    printcap(p2);

    return 0;
}