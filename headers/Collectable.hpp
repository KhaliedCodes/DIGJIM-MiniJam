#pragma once
#include <SFML/Graphics.hpp>

class Collectable {
    sf::Vector2f position;
    sf::Texture texture;
    sf::RectangleShape shape;

  public:
    Collectable(sf::Vector2f position);
    void SetPosition(sf::Vector2f position);
    void render();
    void update();
};
