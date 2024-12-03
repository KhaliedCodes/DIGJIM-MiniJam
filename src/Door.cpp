#include "../headers/Door.hpp"


Door::Door(sf::Vector2f position, int blockSize) {
    this->position =
        sf::Vector2f(position.x / blockSize, position.y / blockSize);
    shape = new sf::RectangleShape();
    this->texture1.loadFromFile("../static/1.png");
    this->texture2.loadFromFile("../static/2.png");
    shape->setPosition(position.x, position.y);
    shape->setSize(sf::Vector2f(blockSize, blockSize));
}

void Door::SetPosition(sf::Vector2f position) { this->position = position; }

void Door::render(sf::RenderWindow& l_window, int Quote) { 
    if (5<=Quote) { 
        (*shape).setTexture(&texture2); 
    }
    else { (*shape).setTexture(&texture1); }
    l_window.draw(*shape);
}

void Door::update() {}

sf::Vector2f Door::getPosition() { return position; }