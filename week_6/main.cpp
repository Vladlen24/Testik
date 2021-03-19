#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <iterator>
#include <chrono>
#include <ctime>
#include <ratio>

using namespace std::chrono_literals;
namespace fs = std::filesystem;

int main()
{
    /*fs::create_directories("data/a/b.txt");
    std::vector<fs::path> paths = {
            "data/a/b.txt/1.txt",
            "data/a/b.txt/2.txt",
            "data/a/3.dat",
            "data/4.dat"
    };
    for (const auto& filepath : paths)
    {
        // В C++17 конструктор fstream принимает как string, так и wstring,
        //  это упрощает кроссплатформенное конструирование его из path
        std::ofstream(filepath.native()) << "test";
    }*/
    fs::path p = fs::current_path();
    auto ftime = fs::last_write_time(p);
    //std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
    //std::cout << "File write time is " << std::asctime(std::localtime(&cftime)) << '\n';
    fs::remove(p);
    time_t tt;
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    tt = std::chrono::system_clock::to_time_t ( today );

    {

        fs::recursive_directory_iterator begin("data");
        fs::recursive_directory_iterator end;
        // Получаем список подкаталогов с помощью алгоритма copy_if
        std::vector<fs::path> subdirs;
        std::copy_if(begin, end, std::back_inserter(subdirs), [](const fs::path& path) {
            return fs::is_directory(path);
        });
        // Выводим список подкаталогов в cout.
        std::cout << "-- subdirs --" << std::endl;
        std::copy(subdirs.begin(), subdirs.end(), std::ostream_iterator<fs::path>(std::cout, "\n"));
    }

    {
        fs::recursive_directory_iterator begin("data");
        fs::recursive_directory_iterator end;

        // Получаем список файлов .txt с помощью алгоритма copy_if
        std::vector<fs::path> txtFiles;
        std::copy_if(begin, end, std::back_inserter(txtFiles), [](const fs::path& path) {
            return fs::is_regular_file(path) && (path.extension() == ".txt");
        });
        // Выводим список файлов в cout.
        std::cout << "-- txt files --" << std::endl;
        std::copy(txtFiles.begin(), txtFiles.end(), std::ostream_iterator<fs::path>(std::cout, "\n"));
    }

    fs::space_info currentVolumeSpace = fs::space(".");
    std::cout << std::setw(15) << "Capacity"
              << std::setw(15) << "Free"
              << std::setw(15) << "Available"
              << "\n"
              << std::setw(15) << currentVolumeSpace.capacity
              << std::setw(15) << currentVolumeSpace.free
              << std::setw(15) << currentVolumeSpace.available
              << "\n";
}

/*    /home/vladlen/Testik/week_6/cmake-build-debug/directory/file.txt      */