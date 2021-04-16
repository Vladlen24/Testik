#include <array>
#include <ctime>
#include <cstdint>
#include <random>

#include <SFML/Graphics.hpp>

using namespace sf;

enum class Box
{
    empty,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    bomb,
    closed,
    flag
};

int main(int argc, char ** argv)
{
    std::default_random_engine dre;
    std::uniform_int_distribution <> uid(0, 4);

    const std::size_t box_size = 32;
    const std::size_t field_size = 10;

    Box grid_back[field_size + 2][field_size + 2];
    Box grid_view[field_size + 2][field_size + 2];

    for (std::size_t i = 1; i <= field_size; ++i)
    {
        for (std::size_t j = 1; j <= field_size; ++j)
        {
            grid_view[i][j] = Box::closed;

            if (uid(dre) == 0)
            {
                grid_back[i][j] = Box::bomb;
            }
            else
            {
                grid_back[i][j] = Box::empty;
            }
        }
    }

    std::size_t counter = 0;

    for (std::size_t i = 1; i <= field_size; ++i)
    {
        for (std::size_t j = 1; j <= field_size; ++j)
        {
            counter = 0;

            if (grid_back[i][j] == Box::bomb) continue;

            if (grid_back[i + 1][j + 0] == Box::bomb) ++counter;
            if (grid_back[i + 0][j + 1] == Box::bomb) ++counter;
            if (grid_back[i - 1][j - 0] == Box::bomb) ++counter;
            if (grid_back[i - 0][j - 1] == Box::bomb) ++counter;
            if (grid_back[i + 1][j + 1] == Box::bomb) ++counter;
            if (grid_back[i - 1][j - 1] == Box::bomb) ++counter;
            if (grid_back[i - 1][j + 1] == Box::bomb) ++counter;
            if (grid_back[i + 1][j - 1] == Box::bomb) ++counter;

            grid_back[i][j] = static_cast <Box> (counter);
        }
    }

    RenderWindow application(VideoMode(384, 384), "MINESWEEPER");

    Texture texture;

    texture.loadFromFile("images_1/tiles.jpg");

    Sprite sprite(texture);

    Vector2i position;

    std::size_t box_number_x = 0;
    std::size_t box_number_y = 0;

    auto updated = false;

    Event event;

    while (application.isOpen())
    {
        position = Mouse::getPosition(application);

        box_number_x = position.x / box_size;
        box_number_y = position.y / box_size;

        updated = false;

        while (application.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                application.close();
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (1 <= box_number_x && box_number_x <= field_size &&
                    1 <= box_number_y && box_number_y <= field_size)
                {
                    if (event.key.code == Mouse::Left)
                    {
                        grid_view[box_number_x][box_number_y] = grid_back[box_number_x][box_number_y];
                    }
                    else if (event.key.code == Mouse::Right)
                    {
                        grid_view[box_number_x][box_number_y] = Box::flag;
                    }

                    updated = true;
                }
            }
        }

        application.clear(Color::White);

        for (std::size_t i = 1; i <= field_size; ++i)
        {
            for (std::size_t j = 1; j <= field_size; ++j)
            {
                if (updated && grid_view[box_number_x][box_number_y] == Box::bomb)
                {
                    grid_view[i][j] = grid_back[i][j];
                }

                sprite.setTextureRect(IntRect(
                        static_cast <int> (grid_view[i][j]) * box_size, 0, box_size, box_size));

                sprite.setPosition(
                        static_cast <float> (i * box_size),
                        static_cast <float> (j * box_size));

                application.draw(sprite);
            }
        }

        application.display();
    }

    return EXIT_SUCCESS;
}