#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

using namespace boost::interprocess;

int main()
{
    shared_memory_object::remove("shm");
    managed_shared_memory managed_shm{open_or_create, "shm", 1024};
    int *i = managed_shm.find_or_construct<int>("Integer")(0);
    int *j = managed_shm.find_or_construct<int>("Parametr1")();
    int *k = managed_shm.find_or_construct<int>("Parametr2")();
    interprocess_mutex *mtx =
            managed_shm.find_or_construct<interprocess_mutex>("mtx")();
    interprocess_condition *cnd =
            managed_shm.find_or_construct<interprocess_condition>("cnd")();
    scoped_lock<interprocess_mutex> lock{*mtx};
    int a = 0;
    while (*i < 10)
    {

        std::cout << "Message for you: " << *k << std::endl;
        std::cout << "Write your message: " << std::endl;
        std::cin >> a;
        *j = a;

        ++(*i);
        cnd->notify_all();
        cnd->wait(lock);
    }
    cnd->notify_all();
    shared_memory_object::remove("shm");
}