#include <SFML/Graphics.hpp>

#include "../headers/Snake.hpp"
#include "vector"

using namespace sf;

class World {
  public:
    World(sf::Vector2u l_windSize);
    ~World();
    int GetBlockSize();
    void RespawnApple();
    void Update(Snake& l_player);
    void Render(sf::RenderWindow& l_window);
    void ReadWorld();
    void GenerateMovingWalls();
    void DropApple(Snake& l_player);
    bool CheckCollisionWithWalls(sf::Vector2i& m);
    void MoveWalls();

  private:
    sf::Vector2u m_windowSize;
    sf::Vector2i m_apple;
    sf::Vector2i m_shield;
    sf::Vector2i m_slow;
    sf::Vector2i m_verticalWall;
    sf::Vector2i m_horizontalWall;
    int m_blockSize;
    sf::CircleShape m_appleShape;
    sf::RectangleShape m_shieldShape;
    sf::CircleShape m_slowShape;
    sf::RectangleShape m_bounds[4];
    std::vector<std::vector<RectangleShape*>> grid;
    std::vector<RectangleShape*> m_verticalWallShape;
    std::vector<RectangleShape*> m_horizontalWallShape;
    Direction m_verticalWallDirection;
    Direction m_horizontalWallDirection;
    std::vector<sf::Vector2i> m_apples; // To store the positions of the apples
    std::vector<sf::CircleShape> m_appleShapes; // To store the shapes of the apples
     sf::Clock m_fallClock;  // New clock for additional timing
    sf::Clock m_clock;
};