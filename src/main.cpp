#include <SFML/Graphics.hpp>
#include <iostream>

#include "../headers/Game.hpp"

// #include "../headers/Game.hpp"
#include "../headers/GUI.hpp"
#include "../headers/Game.hpp"
#include "string"
using namespace sf;
using namespace std;
void createText(string textString, Text &text) {}
int main() {
    // Program entry point.
    auto startPosition = Vector2f(380, 200);
    auto exitPosition = Vector2f(380, 400);

    GUI gui;
    auto startButton =
        gui.createButton(startPosition, Vector2f(300, 50), Color::Blue);
    auto exitButton =
        gui.createButton(exitPosition, Vector2f(300, 50), Color::Green);

    sf::Font font;
    font.loadFromFile("../static/perpetua.ttf");
    Text startText = Text();
    startText.setFont(font);  // font is a sf::Font
    startText.setString("start");
    startText.setCharacterSize(24);  // in pixels, not points!
    startText.setFillColor(sf::Color::White);
    startText.setOutlineThickness(1);
    startText.setOutlineColor(sf::Color::Black);
    startText.setStyle(sf::Text::Bold);
    // auto startTextPosition = Vector2f(350, 200);
    startText.setPosition(startPosition);

    Text exitText = Text();
    exitText.setFont(font);  // font is a sf::Font
    exitText.setString("Exit");
    exitText.setCharacterSize(24);  // in pixels, not points!
    exitText.setFillColor(sf::Color::White);
    exitText.setOutlineThickness(1);
    exitText.setOutlineColor(sf::Color::Black);
    exitText.setStyle(sf::Text::Bold);
    // auto exitTextPosition = Vector2f(350, 200);
    exitText.setPosition(exitPosition);

    Game game;  // Creating our game obadject.
    auto gameWindow = game.GetWindow()->getWindow();

    bool gameOver = false;
    bool buttonClicked = false;

    while (!game.GetWindow()->IsDone() && !buttonClicked) {
        // Game loop.
        gui.gui_start(*gameWindow, startButton, exitButton, startText,
                      exitText);

        sf::Event event;
        while (gameWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                buttonClicked = true;
                gameOver = true;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                auto mousePosition = Mouse::getPosition(*gameWindow);
                if (gui.isButtonClicked(startButton, mousePosition)) {
                    buttonClicked = true;
                }
                if (gui.isButtonClicked(exitButton, mousePosition)) {
                    buttonClicked = true;
                    gameOver = true;
                }
                cout << "help" << endl;
            }
        }
    }

    while (!game.GetWindow()->IsDone() && !gameOver) {
        game.HandleInput();
        game.Update();
        game.Render();
        game.RestartClock();
    }
    return 0;
}
