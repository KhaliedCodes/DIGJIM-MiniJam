#include "../headers/GUI.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// Function to create a button
sf::RectangleShape GUI::createButton(const sf::Vector2f& position,
                                     const sf::Vector2f& buttonsize,
                                     const sf::Color& color) {
    sf::RectangleShape button(buttonsize);
    button.setPosition(position);
    button.setFillColor(color);
    button.setOrigin(buttonsize.x / 2.3, buttonsize.y / 5);
    return button;
}

// Function to check if a button is clicked
bool GUI::isButtonClicked(sf::RectangleShape& button, sf::Vector2i& mousePos) {
    return button.getGlobalBounds().contains(
        static_cast<sf::Vector2f>(mousePos));
}

int GUI::gui_start(sf::RenderWindow& window, sf::RectangleShape& startButton,
                   sf::RectangleShape& exitButton, sf::Text& startText,
                   sf::Text& exitText) {
    window.clear(sf::Color::Black);
    window.draw(startButton);
    window.draw(exitButton);
    window.draw(startText);
    window.draw(exitText);
    window.display();
    return 0;
}
