#include "../headers/StartingDoor.hpp"

StartingDoor::StartingDoor(sf::Vector2f position, int blockSize) {
    this->position =
        sf::Vector2f(position.x / blockSize, position.y / blockSize);
    shape = new sf::RectangleShape();
    clock.restart();
    this->texture1.loadFromFile("../static/01.png");
    this->texture2.loadFromFile("../static/02.png");
    shape->setPosition(position.x, position.y);
    shape->setSize(sf::Vector2f(blockSize, blockSize));
}

void StartingDoor::SetPosition(sf::Vector2f position) { this->position = position; }

void StartingDoor::render(sf::RenderWindow& l_window) {
    if (clock.getElapsedTime().asSeconds() >= 10) { 
        (*shape).setTexture(&texture2); 
    }
    else { (*shape).setTexture(&texture1); }
    l_window.draw(*shape);
}

void StartingDoor::update() {}

sf::Vector2f StartingDoor::getPosition() { return position; }