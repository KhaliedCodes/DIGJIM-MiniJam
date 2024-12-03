#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

class GUI
{
public:
    sf::RectangleShape createButton(const sf::Vector2f& position, const sf::Vector2f& buttonsize, const sf::Color& color);
    bool isButtonClicked(sf::RectangleShape& button, sf::Vector2i& mousePos);
    int gui_start(sf::RenderWindow& window, sf::RectangleShape& startButton, sf::RectangleShape& exitButton, sf::Text& startText, sf::Text& exitText);
};

#endif
