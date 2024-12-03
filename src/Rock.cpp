#include "../headers/Rock.hpp"

Rock::Rock(sf::Vector2f position, int blockSize, sf::Texture texture) {
    this->position =
        sf::Vector2f(position.x / blockSize, position.y / blockSize);
    shape = new sf::RectangleShape();
    this->texture = texture;
    shape->setPosition(position.x, position.y);
    shape->setTexture(&this->texture);
    // shape->setFillColor(sf::Color::Red);
    shape->setSize(sf::Vector2f(blockSize, blockSize));
}

void Rock::SetPosition(sf::Vector2f position) { this->position = position; }

void Rock::render(sf::RenderWindow& l_window) { l_window.draw(*shape); }

void Rock::update(int blockSize) {
    this->shape->setPosition(position.x * blockSize, position.y * blockSize);
}

sf::Vector2f Rock::getPosition() { return position; }
