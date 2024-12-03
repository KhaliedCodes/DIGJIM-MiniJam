#include "../headers/Snake.hpp"

#include "../headers/Rock.hpp"
Snake::Snake(int l_blockSize) {
    m_size = l_blockSize;
    m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
    if (texture.loadFromFile("../static/hungy.png")) {
        m_bodyRect.setTexture(&texture);
    }

    Reset();
}
Snake::~Snake() {}

void Snake::SetDirection(Direction l_dir) { m_dir = l_dir; }
void Snake::Reset() {
    m_snakeBody.clear();
    m_snakeBody.push_back(SnakeSegment(5, 7));
    SetDirection(Direction::None);  // Start off still.
    m_speed = 10;
    m_lives = 3;
    m_score = 0;
    m_lost = false;
    shield = false;
}

Direction Snake::GetDirection() { return m_dir; }
int Snake::GetSpeed() { return m_speed; }
sf::Vector2i Snake::GetPosition() {
    return (!m_snakeBody.empty() ? m_snakeBody.front().position
                                 : sf::Vector2i(1, 1));
}
int Snake::GetLives() { return m_lives; }
int Snake::GetScore() { return m_score; }
void Snake::IncreaseScore() { m_score += 10; }
bool Snake::HasLost() { return m_lost; }
void Snake::Lose() { m_lost = true; }
void Snake::ToggleLost() { m_lost = !m_lost; }

void Snake::Move(std::vector<std::vector<RectangleShape*>> grid,
                 std::vector<Rock*> rocks, int m_blockSize) {
    for (int i = m_snakeBody.size() - 1; i > 0; --i) {
        m_snakeBody[i].position = m_snakeBody[i - 1].position;
    }
    if (m_dir == Direction::Left) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (GetPosition().x - 1 ==
                        (grid[i][j]->getPosition().x / m_blockSize) &&
                    GetPosition().y ==
                        (grid[i][j]->getPosition().y / m_blockSize)) {
                    return;
                }
            }
        }
        for (int i = 0; i < rocks.size(); i++) {
            if (GetPosition().x - 1 ==
                    (rocks[i]->getPosition().x / m_blockSize) &&
                GetPosition().y == (rocks[i]->getPosition().y / m_blockSize)) {
                return;
            }
        }
        --m_snakeBody[0].position.x;
        m_dir = Direction::None;
    } else if (m_dir == Direction::Right) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (GetPosition().x + 1 ==
                        (grid[i][j]->getPosition().x / m_blockSize) &&
                    GetPosition().y ==
                        (grid[i][j]->getPosition().y / m_blockSize)) {
                    return;
                }
            }
        }
        for (int i = 0; i < rocks.size(); i++) {
            if (GetPosition().x + 1 ==
                    (rocks[i]->getPosition().x / m_blockSize) &&
                GetPosition().y == (rocks[i]->getPosition().y / m_blockSize)) {
                return;
            }
        }
        ++m_snakeBody[0].position.x;
        m_dir = Direction::None;
    } else if (m_dir == Direction::Up) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (GetPosition().x ==
                        (grid[i][j]->getPosition().x / m_blockSize) &&
                    GetPosition().y - 1 ==
                        (grid[i][j]->getPosition().y / m_blockSize)) {
                    return;
                }
            }
        }
        for (int i = 0; i < rocks.size(); i++) {
            if (GetPosition().x == (rocks[i]->getPosition().x / m_blockSize) &&
                GetPosition().y - 1 ==
                    (rocks[i]->getPosition().y / m_blockSize)) {
                return;
            }
        }
        --m_snakeBody[0].position.y;
        m_dir = Direction::None;
    } else if (m_dir == Direction::Down) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (GetPosition().x ==
                        (grid[i][j]->getPosition().x / m_blockSize) &&
                    GetPosition().y + 1 ==
                        (grid[i][j]->getPosition().y / m_blockSize)) {
                    return;
                }
            }
        }
        for (int i = 0; i < rocks.size(); i++) {
            if (GetPosition().x == (rocks[i]->getPosition().x / m_blockSize) &&
                GetPosition().y + 1 ==
                    (rocks[i]->getPosition().y / m_blockSize)) {
                return;
            }
        }
        ++m_snakeBody[0].position.y;
        m_dir = Direction::None;
    }
}

void Snake::MoveReverse() {
    for (int i = 0; i < m_snakeBody.size() - 1; ++i) {
        m_snakeBody[i].position = m_snakeBody[i + 1].position;
    }
}

void Snake::Render(sf::RenderWindow& l_window) {
    if (m_snakeBody.empty()) {
        return;
    }
    auto head = m_snakeBody.begin();
    // m_bodyRect.setFillColor(sf::Color::Yellow);

    m_bodyRect.setPosition(head->position.x * m_size,
                           head->position.y * m_size);
    l_window.draw(m_bodyRect);
    // m_bodyRect.setFillColor(sf::Color::Green);

    for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
        m_bodyRect.setPosition(itr->position.x * m_size,
                               itr->position.y * m_size);
        l_window.draw(m_bodyRect);
    }
}

void Snake::IncreaseSpeed() { m_speed++; }
void Snake::DecreaseSpeed() {
    m_speed -= 5;
    m_speed < 10 ? m_speed = 10 : m_speed;
}

void Snake::DisplayScore(sf::RenderWindow& l_window) {
    sf::Font font;
    if (!font.loadFromFile("../static/perpetua.ttf")) return;

    sf::Text scoreText = sf::Text();
    scoreText.setFont(font);  // font is a sf::Font
    scoreText.setString("Score: " + std::to_string(m_score));
    scoreText.setCharacterSize(24);  // in pixels, not points!
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setOutlineThickness(1);
    scoreText.setOutlineColor(sf::Color::Yellow);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(sf::Vector2f(16, 16));
    l_window.draw(scoreText);

    sf::Text speedText = sf::Text();
    speedText.setFont(font);  // font is a sf::Font
    speedText.setString("Speed: " + std::to_string(m_speed));
    speedText.setCharacterSize(24);  // in pixels, not points!
    speedText.setFillColor(sf::Color::Green);
    speedText.setOutlineThickness(1);
    speedText.setOutlineColor(sf::Color::Yellow);
    speedText.setStyle(sf::Text::Bold);
    speedText.setPosition(sf::Vector2f(16, 48));
    l_window.draw(speedText);
}

SnakeContainer Snake::GetSnakeBody() { return m_snakeBody; }

void Snake::setPosition(Vector2f position) {
    this->m_snakeBody[0].position.x = position.x / 64;
    this->m_snakeBody[0].position.y = position.y / 64;
}