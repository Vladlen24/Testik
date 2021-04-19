#include <SFML/Graphics.hpp>
#include <iostream>

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

        sf::Font font;
        font.loadFromFile("arial.ttf");
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cout << "Error..." << std::endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setString("Hello world");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        window.draw(text);

        window.display();
    }

    return 0;
}
