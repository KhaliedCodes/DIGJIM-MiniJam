#include "../headers/Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

Game::~Game() {}
Game::Game()
    : m_window("Snake", sf::Vector2u(800, 600)),
      m_snake(m_world.GetBlockSize()),
      m_world(sf::Vector2u(800, 600), m_snake) {}
void Game::Update() {
    float timestep = 1.0f / 60;
    if (m_elapsed.asSeconds() >= timestep) {
        m_world.Update(m_snake);
        if (m_snake.HasLost()) {
            m_snake.Reset();
        }

        m_elapsed -= sf::seconds(timestep);
    }
    m_window.Update();  // Update window events.
}

void Game::Render() {
    m_window.BeginDraw();  // Clear.

    sf::View view = m_window.m_window.getView();
    view.setCenter(
        sf::Vector2f(m_snake.GetPosition().x * m_world.GetBlockSize(),
                     m_snake.GetPosition().y * m_world.GetBlockSize()));
    m_window.m_window.setView(view);
    m_world.Render(m_window.m_window);
    m_snake.Render(m_window.m_window);  // Display.
    m_snake.DisplayScore(m_window.m_window);
    m_window.EndDraw();
}

void Game::HandleInput() {
    sf::Event event;
    while (m_window.m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.m_isDone = true;
        }
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                sf::View view = m_window.m_window.getView();
                if (view.getSize().x <
                    m_window.m_window.getDefaultView().getSize().x * 2) {
                    float zoomFactor =
                        (event.mouseWheelScroll.delta > 0) ? 1.0f : 1.1f;
                    view.zoom(zoomFactor);
                    m_window.m_window.setView(view);
                }
                if (view.getSize().x >
                    m_window.m_window.getDefaultView().getSize().x / 2) {
                    float zoomFactor =
                        (event.mouseWheelScroll.delta > 0) ? 0.9f : 1.0f;
                    view.zoom(zoomFactor);
                    m_window.m_window.setView(view);
                }
            }
        }
        if (event.type == Event::KeyPressed)
            if (event.key.code == Keyboard::Up) {
                m_snake.SetDirection(Direction::Up);
                m_snake.Move(m_world.grid, m_world.rocks,
                             m_world.GetBlockSize());
            } else if (event.key.code == Keyboard::Down) {
                m_snake.SetDirection(Direction::Down);
                m_snake.Move(m_world.grid, m_world.rocks,
                             m_world.GetBlockSize());
            } else if (event.key.code == Keyboard::Left) {
                m_snake.SetDirection(Direction::Left);
                m_snake.Move(m_world.grid, m_world.rocks,
                             m_world.GetBlockSize());
            } else if (event.key.code == Keyboard::Right) {
                m_snake.SetDirection(Direction::Right);
                m_snake.Move(m_world.grid, m_world.rocks,
                             m_world.GetBlockSize());
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    m_snake.SetDirection(Direction::Up);
                    m_snake.Move(m_world.grid, m_world.rocks, m_world.GetBlockSize());
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    m_snake.SetDirection(Direction::Down);
                    m_snake.Move(m_world.grid, m_world.rocks, m_world.GetBlockSize());
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    m_snake.SetDirection(Direction::Left);
                    m_snake.Move(m_world.grid, m_world.rocks, m_world.GetBlockSize());
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    m_snake.SetDirection(Direction::Right);
                    m_snake.Move(m_world.grid, m_world.rocks, m_world.GetBlockSize());
                }
            }
    }
}

sf::Time Game::GetElapsed() { return m_elapsed; }
void Game::RestartClock() { m_elapsed += m_clock.restart(); }

GameWindow* Game::GetWindow() { return &m_window; }