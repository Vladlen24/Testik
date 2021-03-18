#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <iterator>

namespace fs = std::filesystem;

int main()
{
    fs::create_directories("data/a/b.txt");
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
    }


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
}

/*    /home/vladlen/Testik/week_6/cmake-build-debug/directory/file.txt      */