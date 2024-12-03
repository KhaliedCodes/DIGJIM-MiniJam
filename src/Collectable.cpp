#include "../headers/Collectable.hpp"

Collectable::Collectable(sf::Vector2f position, int blockSize,
                         sf::Texture texture) {
    this->position =
        sf::Vector2f(position.x / blockSize, position.y / blockSize);
    shape = new sf::RectangleShape();
    this->texture = texture;
    shape->setPosition(position.x, position.y);
    shape->setTexture(&this->texture);
    shape->setSize(sf::Vector2f(blockSize, blockSize));
}
void Collectable::update(int blockSize) {
    this->shape->setPosition(position.x * blockSize, position.y * blockSize);
}
void Collectable::SetPosition(sf::Vector2f position) {
    this->position = position;
}

void Collectable::render(sf::RenderWindow& l_window) { l_window.draw(*shape); }
sf::Vector2f Collectable::getPosition() { return position; }