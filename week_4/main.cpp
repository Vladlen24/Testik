#include <iostream>
#include <list>
#include <numeric>
#include <vector>

int main() {

    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);

    for (auto elem: v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
