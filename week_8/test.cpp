#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>

using namespace boost::interprocess;

int main() {
    shared_memory_object::remove("shm");
    managed_shared_memory managed_shm{open_or_create, "shm", 1024};
    typedef allocator<char,
            managed_shared_memory::segment_manager> CharAllocator;
    typedef basic_string<char, std::char_traits<char>, CharAllocator> string;
    int *i = managed_shm.find_or_construct<int>("Integer")(0);
    string *j = managed_shm.find_or_construct<string>("String1")("", managed_shm.get_segment_manager());
    string *k = managed_shm.find_or_construct<string>("String2")("", managed_shm.get_segment_manager());
    interprocess_mutex *mtx =
            managed_shm.find_or_construct<interprocess_mutex>("mtx")();
    interprocess_condition *cnd =
            managed_shm.find_or_construct<interprocess_condition>("cnd")();
    scoped_lock<interprocess_mutex> lock{*mtx};
    std::string str = "Hello";
    while (*i < 10) {

        std::cout << "You have a message: " << *k << std::endl;
        std::cout << "Write your message: " << std::endl;
        std::cin >> str;
        j->clear();
        j->insert(0, str);

        ++(*i);
        cnd->notify_all();
        cnd->wait(lock);
    }
    cnd->notify_all();
    shared_memory_object::remove("shm");
}