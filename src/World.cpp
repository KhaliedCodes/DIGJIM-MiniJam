#include "../headers/World.hpp"

#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
World::World(sf::Vector2u l_windSize) {
    m_blockSize = 128;
    m_windowSize = l_windSize;
    RespawnApple();
    // RespawnShield();
    // GenerateMovingWalls();
    // m_horizontalWallDirection = Direction::Right;
    // m_verticalWallDirection = Direction::Down;
    // m_slowShape.setPosition(-100, -100);
    // m_appleShape.setFillColor(sf::Color::Red);

    sf::Texture wallTexture;

    wallTexture.loadFromFile("../static/Golden fish.png");
    m_appleShape.setTexture(&wallTexture);
    m_appleShape.setRadius(m_blockSize / 2);
    // m_shieldShape.setFillColor(sf::Color::Blue);
    // m_shieldShape.setSize(sf::Vector2f(m_blockSize, m_blockSize));
    // m_slowShape.setFillColor(sf::Color::Green);
    // m_slowShape.setRadius(m_blockSize / 2);
    // for (int i = 0; i < 4; ++i) {
    //     m_bounds[i].setFillColor(sf::Color(150, 0, 0));
    //     if (!((i + 1) % 2)) {
    //         m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
    //     } else {
    //         m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
    //     }
    //     if (i < 2) {
    //         m_bounds[i].setPosition(0, 0);
    //     } else {
    //         m_bounds[i].setOrigin(m_bounds[i].getSize());
    //         m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
    //     }
    // }

    ReadWorld();
    m_clock.restart();
}

void World::RespawnApple() {
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;
    m_apple = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
    bool overlapped = false;
    do {
        cout << "inside loop" << endl;
        bool overlapped = CheckCollisionWithWalls(m_apple);
    } while (overlapped);
    m_appleShape.setPosition(m_apple.x * m_blockSize, m_apple.y * m_blockSize);
}

bool World::CheckCollisionWithWalls(sf::Vector2i& m) {
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (m.x == (grid[i][j]->getPosition().x / m_blockSize) &&
                m.y == (grid[i][j]->getPosition().y / m_blockSize)) {
                m = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
                cout << "iI'M INNN" << endl;
                return true;
            }
        }
    }
    return false;
}

void World::Update(Snake& l_player) {
    // MoveWalls();
    if (l_player.GetPosition() == m_apple) {
        cout << "eated?" << endl;
        // l_player.Extend();
        l_player.IncreaseScore();
        l_player.IncreaseSpeed();
        RespawnApple();
    }

    // if (l_player.GetPosition() == m_shield) {
    //     l_player.SetShield();
    //     m_shieldShape.setPosition(-111, -111);
    //     m_shield = sf::Vector2(-111, -111);
    // }
    // if (l_player.GetPosition() == m_slow) {
    //     l_player.DecreaseSpeed();
    //     m_slowShape.setPosition(-111, -111);
    //     m_slow = sf::Vector2(-111, -111);
    // }
    auto elapsed = m_clock.getElapsedTime().asSeconds();
    // if (((int)elapsed % 30) == 0 && (int)elapsed != 0 &&
    //     m_shieldShape.getPosition().x < 0) {
    //     RespawnShield();
    // }
    // if (((int)elapsed % 30) == 0 && (int)elapsed != 0 &&
    //     m_slowShape.getPosition().x < 0) {
    //     RespawnSlow();
    // }
    int gridSize_x = m_windowSize.x / m_blockSize;
    int gridSize_y = m_windowSize.y / m_blockSize;
    if (l_player.GetPosition().x <= 0 || l_player.GetPosition().y <= 0 ||
        l_player.GetPosition().x >= gridSize_x - 1 ||
        l_player.GetPosition().y >= gridSize_y - 1) {
        // if (l_player.HasShield()) {
        //     l_player.LoseShield();
        //     l_player.SetDirection(Direction::None);
        //     l_player.MoveReverse();
        // } else {
        //     l_player.Lose();
        //     RespawnApple();
        //     RespawnShield();
        //     GenerateMovingWalls();
        //     m_clock.restart();
        // }
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            // if (l_player.GetPosition().x ==
            //         (grid[i][j]->getPosition().x / m_blockSize) &&
            //     l_player.GetPosition().y ==
            //         (grid[i][j]->getPosition().y / m_blockSize))
            //     if (l_player.HasShield()) {
            //         l_player.LoseShield();
            //         l_player.SetDirection(Direction::None);
            //         l_player.MoveReverse();
            //     } else {
            //         RespawnApple();
            //         m_clock.restart();
            //         l_player.Lose();
            //     }

            l_player.MoveReverse();
        }
    }
}

void World::Render(sf::RenderWindow& l_window) {
    for (int i = 0; i < 4; ++i) {
        l_window.draw(m_bounds[i]);
    }
    for (int i = 0; i < m_verticalWallShape.size(); ++i) {
        l_window.draw((*m_verticalWallShape[i]));
    }
    for (int i = 0; i < m_horizontalWallShape.size(); ++i) {
        l_window.draw((*m_horizontalWallShape[i]));
    }
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            l_window.draw((*grid[i][j]));
        }
    }
    l_window.draw(m_appleShape, sf::BlendAdd);
    l_window.draw(m_shieldShape, sf::BlendAdd);
    l_window.draw(m_slowShape, sf::BlendAdd);
}

int World::GetBlockSize() { return m_blockSize; }
World::~World() {}

sf::Texture wallTexture;
void World::ReadWorld() {
    const string& path = "../static/grid.txt";
    ifstream myfile(path, ios_base::in);

    if (!myfile.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    string line;
    int row = 0;
    int winY = 0;

    wallTexture.loadFromFile("../static/snowSeamless.png");
    while (getline(myfile, line)) {
        grid.push_back(std::vector<RectangleShape*>());
        for (int col = 0, winX = 0;
             /*winX < m_windowSize.x &&*/ line[col] != '\0';
             col++, winX += m_blockSize) {
            if (line[col] == '#') {
                auto block = new RectangleShape();
                grid[row].push_back(block);
                (*block).setPosition(sf::Vector2f(winX, winY));
                (*block).setSize(sf::Vector2f(m_blockSize, m_blockSize));
                block->setTexture(&wallTexture);
                // (*block).setFillColor(sf::Color(150, 0, 0));
            }
        }
        row++;
        winY += m_blockSize;
    }

    myfile.close();
}
