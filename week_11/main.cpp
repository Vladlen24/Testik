#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 300), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(250,220,100,50));

        sf::Texture texture;

        // Подгружаем нашу текстуру из файла texture.png
        texture.loadFromFile("/home/vladlen/Рабочий стол/pdf/Врата/vrata-2.jpg");

        // Создаем спрайт и устанавливаем ему нашу текстуру
        sf::Sprite sprite(texture);

        //sprite.setColor(sf::Color::Green);

        // Отрисовка спрайта
        window.draw(sprite);

        window.display();
    }

    return 0;
}
