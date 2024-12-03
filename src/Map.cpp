#include "Map.h"

Map::Map() : window(sf::VideoMode(w, h), "Snake Game!") {
    loadTextures();

    danger.SetPosition(rand() % (N - 1), rand() % (M - 1));
    collectable.SetPosition(rand() % (N - 1), rand() % (M - 1));

    loadMap("map.txt");
}

void Map::  loadTextures() {
    t_collectable.loadFromFile("images/green.png");
    t_danger.loadFromFile("images/red.png");
    t3.loadFromFile("images/white.png");


    s_collectable.setTexture(t_collectable);
    s_danger.setTexture(t_danger);
    s3.setTexture(t3);
}

void Map:: loadMap(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        map.push_back(std::vector<char>(line.begin(), line.end()));
    }
}

void Map::render() {
    window.clear();
    drawMap();
    drawEntities();
    window.display();
}

void Map::drawMap() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == '*') {
                s_collectable.setPosition(i * size, j * size);
                window.draw(s_collectable);
            }
            else if (map[i][j] == '/') {
                s_danger.setPosition(i * size, j * size);
                window.draw(s_danger);
            }
            else {
                s3.setPosition(i * size, j * size);
                window.draw(s3);
            }
        }
    }
}

void Map::drawEntities() {
    s_collectable.setPosition(collectable.x * size, collectable.y * size);
    s_danger.setPosition(danger.x * size, danger.y * size);

    window.draw(s_collectable);
    window.draw(s_danger);

    if (sf::Event::Closed) window.close();
}

void Map::run() {
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }

        //update();
        render();
    }
}