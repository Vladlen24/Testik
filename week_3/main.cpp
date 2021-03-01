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
#include <functional>
#include <string>
#include <unordered_set>

//--------------------------------------ЗАДАНИЕ №4------------------------------------------------------------
const char* get_rand_string() {

    const char* s = "";
    srand(time(nullptr));
    int64_t l = rand() % 10;
    for (int i = 0; i < 10; ++i) {
        char a(rand() % 20 + 97);
        s += a;
    }

    return s;
}

unsigned int RSHash(const char* str, unsigned int length)
{
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = hash * a + (*str);
        a    = a * b;
    }

    return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
    const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits          =
            (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i    = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}
//------------------------------------------------------------------------------------------------------------

template < typename T >
void hash_combine(std::size_t & seed, const T & value) noexcept
{
    seed ^= std::hash < T > ()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t & seed, const T & value) noexcept
{
    hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t & seed, const T & value, const Types & ... args) noexcept
{
    hash_combine(seed, value);
    hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}

class Customer
{
private:
    friend struct Customer_Hash;
    friend struct Customer_Equal;

public:
    explicit Customer(const std::string & name, const std::size_t mark) :
            m_name(name), m_mark(mark)
    {}

    ~Customer() noexcept = default;

public:
    friend std::ostream & operator << (std::ostream & stream, const Customer & customer)
    {
        return (stream << customer.m_name << "," << customer.m_mark);
    }

private:
    std::string m_name;
    std::size_t m_mark;
};

struct Customer_Hash
{
    std::size_t operator() (const Customer & customer) const noexcept
    {
        return hash_value(customer.m_name, customer.m_mark);
    }
};

struct Customer_Equal
{
    bool operator() (const Customer & lhs, const Customer & rhs) const noexcept
    {
        return (lhs.m_name == rhs.m_name);
    }
};

std::string get_rand_name() {

    std::string s = "";
    srand(time(nullptr));
    int64_t l = rand() % 10;
    for (int i = 0; i < 10; ++i) {
        char a(rand() % 20 + 97);
        s += a;
    }

    return s;
}

int64_t get_rand_mark() {

    srand(time(nullptr));

    return rand() % 10;
}

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

    //----------------------------------------ЗАДАНИЕ №3-----------------------------------------------------------
    std::unordered_set < Customer, Customer_Hash, Customer_Equal > customers;

    for (int i = 0; i < 1000; ++i) {
        customers.insert(Customer(get_rand_name(), get_rand_mark()));
    }

    std::set<uint64_t> customers_hash;

    for (const auto & customer : customers)
    {
        customers_hash.insert(Customer_Hash()(customer));
    }

    std::cout << "Number of collision (Boost): " << customers.size() - customers_hash.size() << std::endl;

    //-------------------------------------ЗАДАНИЕ №4---------------------------------------------------------------
    {
        std::unordered_set<const char*> strings;                                                                        // RSHash
        //strings.insert(get_rand_string());
        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(RSHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (RSHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   // JSHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(JSHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (JSHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   //PJWHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(PJWHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (PJWHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   // ELFHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(ELFHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (ELFHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   // BKDRHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(BKDRHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (BKDRHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   // SDBMHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(SDBMHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (SDBMHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   // DJBHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(DJBHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (DJBHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   // DEKHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(DEKHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (DEKHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    {                                                                                                                   // APHash
        std::unordered_set<const char*> strings;

        for (int i = 0; i < 100000000; ++i) {
            strings.insert(get_rand_string());
        }

        std::set<int> strings_hash;

        for (const auto & s : strings)
        {
            strings_hash.insert(APHash(s, get_rand_mark()));
        }

        std::cout << "Number of collision (APHash): " << strings.size() - strings_hash.size() << std::endl;
    }

    // по результату проверки худшие показания у APHash (16 коллизий для 10^7 элементов), за ним идет RSHash (9 кол. для 10^7 элем.), потом ELFHash (4 кол. для 10^7 элем.),
    // и у всех остальных нули, для них побольше элементов нужно
    // Ради интереса отдельно рассмотрен случай с RSHash для 10^9 элементов получили 66 коллизий. Внушающее число, то есть как-то многовато

    return 0;
}