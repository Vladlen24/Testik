#include <algorithm>
#include <thread>
#include <vector>
#include <iostream>
#include <functional>
#include <mutex>
#include <atomic>

void f() {
    std::cout << "boo" << std::endl;
}

class Mutex{
public:
    void lock(){
        while(q.exchange(1) != 0){
            //q.wait(1);
        }
    }
    void unlock(){
        q.store(0);
    }
private:
    std::atomic<uint32_t> q{0};
};

int main(int argc, char ** argv)
{
    //std::mutex m;
    Mutex m;
    std::vector<std::thread> threads;
    size_t x = 0;

    threads.reserve(3);
    for (int i =0; i < 3; ++i) {
        threads.emplace_back([&](){
            for (int i = 0; i < 100; ++i) {
                //m.lock();
                //std::lock_guard<std::mutex> lk(m);
                std::lock_guard<Mutex> lk(m);
                ++x;
                //m.unlock();
            }
        });
    }
    for(auto& th: threads){
        th.join();
    }

    std::cout << x << std::endl;

    return EXIT_SUCCESS;
}