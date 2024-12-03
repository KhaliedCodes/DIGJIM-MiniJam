#pragma once
#include <SFML/Graphics.hpp>

class StartingDoor {
    sf::Vector2f position;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::RectangleShape* shape;
    sf::Clock clock;

public:
    StartingDoor(sf::Vector2f position, int blockSize);
    void SetPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void render(sf::RenderWindow& l_window);
    void update();
};