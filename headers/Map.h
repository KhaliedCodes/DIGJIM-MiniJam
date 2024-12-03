#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include"Collectable.h"
#include"Danger.h"
#include <sstream>
#include <fstream>


const int M = 40, N = 30;
const int size = 14;
const int w = size * N;
const int h = size * M;

class Map
{public:
    sf::RenderWindow window;
    sf::Texture t_danger, t_collectable, t3;
    sf::Sprite s_collectable, s_danger, s3;
    std::vector<std::vector<char>> map;
    Danger danger;
    Collectable collectable;

    Map();

    void loadTextures();

    void loadMap(const std::string& filename);

    void render();

    void drawMap();

    void drawEntities() {
        s_collectable.setPosition(collectable.x * size, collectable.y * size);
        s_danger.setPosition(danger.x * size, danger.y * size);

        window.draw(s_collectable);
        window.draw(s_danger);

        if (sf::Event::Closed) window.close();
    }

    void run();
};

