#include <algorithm>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <iterator>

namespace fs = std::filesystem;

int main()
{

    {

        fs::recursive_directory_iterator begin("CMakeFiles");
        fs::recursive_directory_iterator end;
        // Список подкаталогов
        std::vector<fs::path> subdirs;
        std::copy_if(begin, end, std::back_inserter(subdirs), [](const fs::path& path) {
            return fs::is_directory(path);
        });
        std::cout << "-- subdirs --" << std::endl;
        std::copy(subdirs.begin(), subdirs.end(), std::ostream_iterator<fs::path>(std::cout, "\n"));
    }

    {
        fs::recursive_directory_iterator begin("CMakeFiles");
        fs::recursive_directory_iterator end;

        // Cписок файлов
        std::vector<fs::path> Files;
        std::copy_if(begin, end, std::back_inserter(Files), [](const fs::path& path) {
            return fs::is_regular_file(path);
        });
        std::cout << "-- files --" << std::endl;
        std::copy(Files.begin(), Files.end(), std::ostream_iterator<fs::path>(std::cout, "\n"));

        // Можно еще получить список файлов .txt или любого другого необходимого нам расширения, его даже сам пользователь может задавать, КРУТО!
        /*std::vector<fs::path> txtFiles;
        std::copy_if(begin, end, std::back_inserter(txtFiles), [](const fs::path& path) {
            return fs::is_regular_file(path) && (path.extension() == ".txt");
        });*/

    }
}