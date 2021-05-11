#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <boost/interprocess/containers/string.hpp>
#include <thread>

using namespace boost::interprocess;

int main()
{
    shared_memory_object::remove("shm");
    managed_shared_memory managed_shm{open_or_create, "shm", 1024};
    bool *f = managed_shm.find_or_construct<bool>("Flag")(true);
    string *j = managed_shm.find_or_construct<string>("Parametr1")();
    string *k = managed_shm.find_or_construct<string>("Parametr2")();
    interprocess_mutex *mtx =
            managed_shm.find_or_construct<interprocess_mutex>("mtx")();
    interprocess_condition *cnd1 =
            managed_shm.find_or_construct<interprocess_condition>("cnd1")();
    interprocess_condition *cnd2 =
            managed_shm.find_or_construct<interprocess_condition>("cnd2")();
    scoped_lock<interprocess_mutex> lock{*mtx};

    std::thread thread_write ([&](){
        std::string data;
        while (*f) {
            std::cin >> data;
            if (data == "exit") {
                std::cout << "+" << std::endl;
                *f = false;
                //thread_read.~thread();
                cnd1->notify_one();
                cnd2->notify_one();
            }
            *j = data;
            cnd1->notify_one();
            cnd1->wait(lock);
        }
    });

    std::thread thread_read ([&](){
        while (*f) {
            std::cout << "Message for you: " << *k << std::endl;
            cnd2->notify_one();
            cnd2->wait(lock);
        }
    });

    cnd2->notify_one();
    thread_write.join();
    thread_read.join();
    std::cout << "Exit program!" << std::endl;
    shared_memory_object::remove("shm");
}