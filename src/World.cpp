#include "../headers/World.hpp"

#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "../headers/Collectable.hpp"
using namespace std;

//sf::Texture collectibleTexture;
//sf::Texture wallTexture;
World::World(sf::Vector2u l_windSize, Snake& l_player) {
    m_blockSize = 64;
    m_windowSize = l_windSize;
    m_clock.restart();
    quote = 5;
    sf::Texture wallTexture;

    wallTexture.loadFromFile("../static/Golden fish.png");
    m_appleShape.setTexture(&wallTexture);
    m_appleShape.setRadius(m_blockSize / 2);

    ReadWorld(l_player);
    m_clock.restart();
}
void World::Dropjim(Snake& l_player) {
    float fallSpeed = 0.5f;
    float elapsed = m_clockfallClock.getElapsedTime().asSeconds();
    if (elapsed >= fallSpeed) {
        for (auto& collectable : collectables) {
            int nextY = collectable->getPosition().y;
            bool cellOccupied = false;

            for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                    auto blockPos =
                        sf::Vector2f(grid[i][j]->getPosition().x / m_blockSize,
                                     grid[i][j]->getPosition().y / m_blockSize);
                    // cout << blockPos.x << blockPos.y << endl;
                    if (blockPos.x == collectable->getPosition().x &&
                        nextY + 1 == blockPos.y) {
                        cellOccupied = true;
                        cout << "help" << endl;
                        break;
                    }
                }
                if (cellOccupied) break;
            }
            for (auto& otherCollectable : collectables) {
                if (&collectable != &otherCollectable) {
                    if (collectable->getPosition().x ==
                            otherCollectable->getPosition().x &&
                        nextY + 1 == otherCollectable->getPosition().y) {
                        cellOccupied = true;
                        break;
                    }
                }
            }
            for (auto& otherSand : sandBlocks) {
                if (collectable->getPosition().x ==
                        otherSand->getPosition().x &&
                    nextY + 1 == otherSand->getPosition().y) {
                    cellOccupied = true;
                    break;
                }
            }

            if (!cellOccupied) {
                nextY++;
            }

            collectable->SetPosition(
                sf::Vector2f(collectable->getPosition().x, nextY));
        }
        m_clockfallClock.restart();
    }
}

void World::DropRock(Snake& l_player) {
    float fallSpeed = 0.5f;
    float elapsed = m_dropfallClock.getElapsedTime().asSeconds();
    if (elapsed >= fallSpeed) {
        for (auto& rock : rocks) {
            int nextY = rock->getPosition().y;
            bool cellOccupied = false;

            // Check if the cell below the rock is occupied by any other block
            // (sand, collectable, or other rocks)
            for (size_t i = 0; i < grid.size(); i++) {
                for (size_t j = 0; j < grid[i].size(); j++) {
                    auto rockPos =
                        sf::Vector2f(grid[i][j]->getPosition().x / m_blockSize,
                                     grid[i][j]->getPosition().y / m_blockSize);
                    if (rockPos.x == rock->getPosition().x &&
                        nextY + 1 == rockPos.y) {
                        cellOccupied = true;
                        break;
                    }
                }
                if (cellOccupied) break;
            }

            for (auto& otherCollectable : collectables) {
                if (rock->getPosition().x ==
                        otherCollectable->getPosition().x &&
                    nextY + 1 == otherCollectable->getPosition().y) {
                    cellOccupied = true;
                    break;
                }
            }

            for (auto& otherSand : sandBlocks) {
                if (rock->getPosition().x == otherSand->getPosition().x &&
                    nextY + 1 == otherSand->getPosition().y) {
                    cellOccupied = true;
                    break;
                }
            }
            for (auto& otherRock : rocks) {
                if (rock != otherRock) {
                    if (rock->getPosition().x == otherRock->getPosition().x &&
                        nextY + 1 == otherRock->getPosition().y) {
                        cellOccupied = true;
                        break;
                    }
                }
            }
            if (!cellOccupied) {
                nextY++;
            }

            rock->SetPosition(sf::Vector2f(rock->getPosition().x, nextY));
        }

        m_dropfallClock.restart();
    }
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
    if (m_clockfallClock.getElapsedTime().asSeconds() >= appleUpdateInterval) {
        Dropjim(l_player);
        m_clockfallClock.restart();
    }
    if (m_dropfallClock.getElapsedTime().asSeconds() >= appleUpdateInterval) {
        DropRock(l_player);
        m_dropfallClock.restart();
    }
    for (auto& collectable : collectables) {
        if (l_player.GetPosition().x == collectable->getPosition().x &&
            l_player.GetPosition().y == collectable->getPosition().y) {
            cout << "Apple collected!" << endl;
            l_player.IncreaseScore();
            delete (collectable);
            collectables.erase(std::remove(collectables.begin(),
                                           collectables.end(), collectable),
                               collectables.end());
            break;
        }
        collectable->update(m_blockSize);
    }

    for (auto& rock : rocks) {
        if (l_player.GetPosition().x == rock->getPosition().x &&
            l_player.GetPosition().y == rock->getPosition().y) {
            cout << "ded" << endl;
            l_player.Lose();
            break;
        }
        rock->update(m_blockSize);
    }
    for (auto sandBlock = sandBlocks.begin(); sandBlock != sandBlocks.end();
         sandBlock++) {
        if (l_player.GetPosition().x == (*sandBlock)->getPosition().x &&
            l_player.GetPosition().y == (*sandBlock)->getPosition().y) {
            delete (*sandBlock);
            sandBlocks.erase(sandBlock);
            l_player.IncreaseScore();
            break;
        }
    }
    bool isGameWon = false;
    if (l_player.GetPosition().x == door->getPosition().x &&
        l_player.GetPosition().y == door->getPosition().y) {
        cout << "Player Wins!" << endl;
        isGameWon = true;
    }
    auto elapsed = m_clock.getElapsedTime().asSeconds();

    int gridSize_x = m_windowSize.x / m_blockSize;
    int gridSize_y = m_windowSize.y / m_blockSize;
}

void World::Render(sf::RenderWindow& l_window) {
    for (auto& row : grid) {
        for (auto& block : row) {
            l_window.draw(*block);
        }
    }

    for (auto& jimShape : m_appleShapes) {
        l_window.draw(jimShape);
    }

    for (auto& sandBlock : sandBlocks) {
        sandBlock->render(l_window);
    }
    for (auto& collectable : collectables) {
        collectable->render(l_window);
    }
    for (auto& rock : rocks) {
        rock->render(l_window);
    }
    door->render(l_window, quote);
    // startdoor->render(l_window);
}
int World::GetBlockSize() { return m_blockSize; }

void World::ReadWorld(Snake& l_player) {
    const string path = "../static/grid.txt";
    ifstream myfile(path, ios_base::in);

    if (!myfile.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    string line;
    int row = 0;
    int winY = 0;

    sf::Texture sandTexture;
    sf::Texture collectiBleTexture;
    sf::Texture rockTexture;
    sandTexture.loadFromFile("../static/snowSeamless.png");
    // wallTexture.loadFromFile("../static/wall.PNG");
    collectiBleTexture.loadFromFile("../static/Golden fish.png");
    rockTexture.loadFromFile("../static/rock.png");
    while (getline(myfile, line)) {
        grid.push_back(std::vector<RectangleShape*>());
        for (int col = 0, winX = 0;
             /*winX < m_windowSize.x &&*/ line[col] != '\0';
             col++, winX += m_blockSize) {
            if (line[col] == '#') {
                auto block = new sf::RectangleShape();
                block->setPosition(sf::Vector2f(winX, winY));
                block->setSize(sf::Vector2f(m_blockSize, m_blockSize));
                grid[row].push_back(block);
                // block->setTexture(&wallTexture);
            }

            if (line[col] == '@') {
                auto block = new Sand(sf::Vector2f(winX, winY), m_blockSize,
                                      sandTexture);
                sandBlocks.push_back(block);
            }

            if (line[col] == '%') {
                auto block = new Collectable(sf::Vector2f(winX, winY),
                                             m_blockSize, collectiBleTexture);
                collectables.push_back(block);
            }
            if (line[col] == '&') {
                auto block = new Rock(sf::Vector2f(winX, winY), m_blockSize,
                                      rockTexture);
                rocks.push_back(block);
            }
            // if (line[col] == 'A') {
            //     l_player.setPosition(sf::Vector2f(winX, winY));
            // }
            if (line[col] == 'D') {
                door = new Door(sf::Vector2f(winX, winY), m_blockSize);
            }
            // if (line[col] == 'S') {
            //     startdoor = new StartDoor(sf::Vector2f(winX, winY),
            //     m_blockSize);
            // }
        }
        row++;
        winY += m_blockSize;
    }

    myfile.close();
}