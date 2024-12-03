#pragma once
#include <SFML/Graphics.hpp>
class Sand {
    sf::Vector2f position;
    sf::Texture texture;
    sf::RectangleShape* shape;

  public:
    Sand(sf::Vector2f position, int blockSize, sf::Texture texture);
    void SetPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void render(sf::RenderWindow& l_window);
    void update();
};