#pragma once
#include <SFML/Graphics.hpp>
class Door {
    sf::Vector2f position;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::RectangleShape* shape;

  public:
    Door(sf::Vector2f position, int blockSize);
    void SetPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void render(sf::RenderWindow& l_window, int Quote);
    void update();
};