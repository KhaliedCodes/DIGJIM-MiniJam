#pragma once
#include <SFML/Graphics.hpp>

class Collectable {
    sf::Vector2f position;
    sf::Texture texture;
    sf::RectangleShape* shape;

public:
    Collectable(sf::Vector2f position, int blockSize, sf::Texture texture);
    void SetPosition(sf::Vector2f position);
    void render(sf::RenderWindow& l_window);
    void update(int blockSize);
    sf::Vector2f getPosition();
};