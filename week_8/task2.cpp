#include <algorithm>
#include <vector>
#include <iomanip>
#include <iostream>
#include <mutex>

std::vector < char > vector;
std::string s = "GATCGATACA";
std::mutex		   mutex;

int find(std::string value)
{
    std::lock_guard < std::mutex > lock(mutex);
    std::vector<char>::iterator it;
    it = std::find(vector.begin(), vector.end(), value);
    if (it != vector.end()){
        return it-vector.begin()+1;
    }
    else return -1;
}

int main(int argc, char ** argv)
{

    {
        //std::lock_guard < std::mutex > lock(mutex);
        for (int i = 0; i < s.size(); ++i){
            vector.push_back(s[i]);
        }
    }

    std::cout << find("TAC") << std::endl;

    return EXIT_SUCCESS;
}
