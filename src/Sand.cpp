#include "../headers/Sand.hpp"

Sand::Sand(sf::Vector2f position, int blockSize, sf::Texture texture) {
    this->position =
        sf::Vector2f(position.x / blockSize, position.y / blockSize);
    shape = new sf::RectangleShape();
    this->texture = texture;
    shape->setPosition(position.x, position.y);
    shape->setTexture(&this->texture);
    shape->setSize(sf::Vector2f(blockSize, blockSize));
}

void Sand::SetPosition(sf::Vector2f position) { this->position = position; }

void Sand::render(sf::RenderWindow& l_window) { l_window.draw(*shape); }

void Sand::update() {}

sf::Vector2f Sand::getPosition() { return position; }