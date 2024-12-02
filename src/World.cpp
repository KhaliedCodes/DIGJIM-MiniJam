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
    m_clock.restart();
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

void World::GenerateMovingWalls() {
    // Example implementation for moving walls
    m_verticalWallShape.clear();
    m_horizontalWallShape.clear();

    for (int i = 0; i < 3; ++i) {
        auto wall = new sf::RectangleShape();
        wall->setSize(sf::Vector2f(m_blockSize, m_blockSize));
        wall->setFillColor(sf::Color(200, 50, 50));
        wall->setPosition(i * m_blockSize, m_blockSize);
        m_verticalWallShape.push_back(wall);

        auto wallH = new sf::RectangleShape();
        wallH->setSize(sf::Vector2f(m_blockSize, m_blockSize));
        wallH->setFillColor(sf::Color(50, 50, 200));
        wallH->setPosition(m_blockSize, i * m_blockSize);
        m_horizontalWallShape.push_back(wallH);
    }
}
void World::DropApple(Snake& l_player) {
    int maxY = (m_windowSize.y / m_blockSize) - 2;
    float fallSpeed = 1.0f;
    float elapsed = m_fallClock.getElapsedTime().asSeconds(); 
    std::cout << elapsed <<"\n";
    if (elapsed >= fallSpeed) {
        for (auto& apple : m_apples) {
            int nextY = apple.y;

            if (nextY < maxY) {
                sf::Vector2i testPosition(apple.x, nextY + 1);

                bool cellOccupied = false;

                for (size_t i = 0; i < grid.size(); i++) {
                    for (size_t j = 0; j < grid[i].size(); j++) {
                        sf::Vector2f blockPos = grid[i][j]->getPosition();
                       
                        if (testPosition == sf::Vector2i(blockPos.x / m_blockSize, blockPos.y / m_blockSize)) {
                            cellOccupied = true;
                            break;
                        }
                    }
                    if (cellOccupied) break;
                }
                for (auto& otherApple : m_apples) {
                    if (&apple != &otherApple && apple.x == otherApple.x && otherApple.y == nextY + 1) {
                        cellOccupied = true;
                        break;
                    }
                }

                if (!cellOccupied) {
                    nextY++;
                }
            } 
            apple.y = nextY;
            m_appleShapes[&apple - &m_apples[0]].setPosition(apple.x * m_blockSize, apple.y * m_blockSize);
        }
        m_clock.restart();
    }
}
void World::RespawnApple() {
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;

    bool overlapped;
    for (int i = 0; i < 20; ++i) {
        sf::Vector2i newApple;
        do {
            newApple = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
            overlapped = CheckCollisionWithWalls(newApple);
        } while (overlapped);

        m_apples.push_back(newApple);

        sf::CircleShape appleShape(m_blockSize / 2);
        appleShape.setFillColor(sf::Color::Red);
        appleShape.setPosition(newApple.x * m_blockSize, newApple.y * m_blockSize);
        m_appleShapes.push_back(appleShape); 
    }
 //   DropApple();
}

bool World::CheckCollisionWithWalls(sf::Vector2i& m) {
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;

    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {
            if (m.x == (grid[i][j]->getPosition().x / m_blockSize) &&
                m.y == (grid[i][j]->getPosition().y / m_blockSize)) {
                m = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
                return true;
            }
        }
    }
    return false;
}

void World::Update(Snake& l_player) {
    float appleUpdateInterval = 0.5f;
    if (m_clock.getElapsedTime().asSeconds() >= appleUpdateInterval) {
        DropApple(l_player); 
        m_clock.restart();
    }

    for (auto& apple : m_apples) {
        if (l_player.GetPosition() == apple) {
            cout << "Apple collected!" << endl;
            l_player.IncreaseScore();
            m_apples.erase(std::remove(m_apples.begin(), m_apples.end(), apple), m_apples.end());
            m_appleShapes.erase(m_appleShapes.begin() + (&apple - &m_apples[0])); 
            break;
        }
    }

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

  
}

void World::Render(sf::RenderWindow& l_window) {
    for (int i = 0; i < 4; ++i) {
        l_window.draw(m_bounds[i]);
    }
    for (auto& wall : m_verticalWallShape) {
        l_window.draw(*wall);
    }
    for (auto& wall : m_horizontalWallShape) {
        l_window.draw(*wall);
    }
    for (auto& row : grid) {
        for (auto& block : row) {
            l_window.draw(*block);
        }
    }

    for (auto& appleShape : m_appleShapes) {
        l_window.draw(appleShape, sf::BlendAdd);
    }

    l_window.draw(m_shieldShape, sf::BlendAdd);
    l_window.draw(m_slowShape, sf::BlendAdd);
}
int World::GetBlockSize() { return m_blockSize; }

World::~World() {
    for (auto& row : grid) {
        for (auto& block : row) {
            delete block;
        }
    }
    for (auto& wall : m_verticalWallShape) {
        delete wall;
    }
    for (auto& wall : m_horizontalWallShape) {
        delete wall;
    }
}

sf::Texture wallTexture;
void World::ReadWorld() {
    const string path = "../static/grid.txt";
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
                auto block = new sf::RectangleShape();
                block->setPosition(sf::Vector2f(winX, winY));
                block->setSize(sf::Vector2f(m_blockSize, m_blockSize));
                block->setFillColor(sf::Color(150, 0, 0));
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
