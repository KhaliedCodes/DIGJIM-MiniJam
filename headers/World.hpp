#include <SFML/Graphics.hpp>
#include"../headers/Door.hpp"
#include"../headers/StartingDoor.hpp"
#include "../headers/Collectable.hpp"
#include "../headers/Snake.hpp"
using namespace sf;
#include "../headers/Rock.hpp"
#include "Sand.hpp"
#include "vector"

class World {
  public:
    World(sf::Vector2u l_windSize);
    int GetBlockSize();
    void RespawnApple(Vector2f& position);
    void Update(Snake& l_player);
    void Render(sf::RenderWindow& l_window);
    void ReadWorld();
    void DropApple(Snake& l_player);
    bool CheckCollisionWithWalls(sf::Vector2i& m);
    std::vector<std::vector<RectangleShape*>> grid;
    std::vector<Sand*> sandBlocks;
    std::vector<Collectable*> collectables;
    std::vector<Rock*> rocks;

  private:
    sf::Vector2u m_windowSize;
    sf::Vector2i m_apple;
    int m_blockSize;
    int quote;
    sf::CircleShape m_appleShape;
    sf::RectangleShape m_bounds[4];
    Door* door;
    StartingDoor* startdoor;
    std::vector<sf::Vector2i> m_apples;  // To store the positions of the apples
    std::vector<sf::CircleShape>
        m_appleShapes;      // To store the shapes of the apples
    sf::Clock m_fallClock;  // New clock for additional timing
    sf::Clock m_clock;
};