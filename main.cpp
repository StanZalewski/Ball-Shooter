#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Game {
   private:
    int score_;
    sf::Color black;
    sf::Color red;
    sf::Color green;
    sf::Color blue;
    sf::Color yellow;
    sf::Color violet;
    sf::Color purple;

   public:
    
    int score = 0;
    Game()
        : black(sf::Color(0, 0, 0)),
          red(sf::Color(209, 109, 106)),
          green(sf::Color(157, 194, 132)),
          blue(sf::Color(120, 157, 229)),
          yellow(sf::Color(222, 207, 105)),
          purple(sf::Color(107, 34, 70)){};
    void Start();
    int getScore() const;
    void setScore(int score);
    void display();
    void checkIfHitAndDestroy();
};

class Object : public sf::CircleShape {
   protected:
    int position_x_;
    int position_y_;
    sf::Color color_;

   public:
    Object(const sf::Vector2f& size_, const sf::Vector2f& position_, sf::Color color_)
    : sf::CircleShape(size_.x)
    {
        position_x_ = position_.x;
        position_y_ = position_.y;
        setFillColor(color_); // Set the fill color of the circle shape
        setPosition(position_);
    }


    int getPosition_x() const {
        return position_x_;
    }
    void setPosition_x(int position_x) {
        position_x_ = position_x;
    }

    int getPosition_y() const {
        return position_y_;
    }
    void setPosition_y(int position_y) {
        position_y_ = position_y;
    }

    int getSize() const {
        return getRadius();
    }
    void setSize(int size) {
        setRadius(size);
    }

    sf::Color getColor() const {
        return color_;
    }
    void setColor(sf::Color color) {
        color_ = color;
    }
};

class Game_Wall {
private:

public:
    std::vector<std::vector<Object*>> wall_;
    const int width = 40;
    const int height = 37;

    int random_num()
    {
        // Define the probabilities for each number (0-5)
        std::vector<double> probabilities = {0.1, 0.1, 0.1, 0.5, 0.1, 0.1};

        // Calculate the total sum of probabilities
        double totalSum = 0.0;
        for (double prob : probabilities) {
            totalSum += prob;
        }

        // Generate a random number between 0 and the total sum
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0, totalSum);
        double randomValue = dis(gen);

        // Find the corresponding number based on the probabilities
        double sum = 0.0;
        for (int i = 0; i < probabilities.size(); i++) {
            sum += probabilities[i];
            if (randomValue < sum) {
                return i;
            }
        }

        // Default case (shouldn't be reached)
        return 0;
    }

    void addNewRow(int row)
{
    std::vector<sf::Color> colors = {
        sf::Color::Black,
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Yellow,
        sf::Color::Blue,
        sf::Color(128, 0, 128),
    };

    // Resize the wall_ vector if needed
    if (wall_.size() <= row)
        {
            wall_.resize(row + 1, std::vector<Object*>(width, nullptr));
        }

    for (int col = 0; col < width; col++)
        {
            Object* obj = new Object(sf::Vector2f(20.f, 20.f), sf::Vector2f(col * 45.f, row * 45.f), colors[random_num()]);
            wall_[row][col] = obj;
        }
    }   

};

class Game_menu {
private:
public:
     int random_num_menu()
    {
        // Define the probabilities for each number (0-5)
        std::vector<double> probabilities = {0.1, 0.1, 0.1, 0.5, 0.1, 0.1};

        // Calculate the total sum of probabilities
        double totalSum = 0.0;
        for (double prob : probabilities) {
            totalSum += prob;
        }

        // Generate a random number between 0 and the total sum
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0, totalSum);
        double randomValue = dis(gen);

        // Find the corresponding number based on the probabilities
        double sum = 0.0;
        for (int i = 0; i < probabilities.size(); i++) {
            sum += probabilities[i];
            if (randomValue < sum) {
                return i;
            }
        }

        // Default case (shouldn't be reached)
        return 0;
    }

    const int width = 40;
    const int height = 37;


    std::vector<sf::Color> colors = {
        sf::Color::Blue,
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Yellow,
        sf::Color::Black,
        sf::Color(128, 0, 128)
    };

    std::vector<sf::CircleShape> menuItems_;

    Game_menu() {
        menuItems_.resize(width / 2 - 4);
    }

    void addMenu() {
        for (int col = 0; col < width / 2 - 4; col++) {
            menuItems_[col].setRadius(20.f);
            menuItems_[col].setPosition(col * 60.f, 1500.f);
            menuItems_[col].setFillColor(colors[random_num_menu()]);
        }
    }

    std::vector<sf::CircleShape> dowystrzalu;

    void addNewBall() {
        // Check if there are any balls in the vector
        if (menuItems_.empty()) {
            return;
        }

        // Move the last ball 100 pixels higher
        sf::CircleShape& lastBall = menuItems_.back();
        sf::Vector2f currentPosition = lastBall.getPosition();
        lastBall.setPosition(currentPosition.x, currentPosition.y - 125.f);

        // Move the last ball from menuItems to dowystrzalu
        dowystrzalu.push_back(lastBall);
        menuItems_.pop_back();

        // Shift all balls one position further
        for (int i = width / 2 - 4 - 2; i >= 0; i--) {
            sf::CircleShape& ball = menuItems_[i];
            sf::Vector2f nextPosition = ball.getPosition();
            ball.setPosition(currentPosition.x, currentPosition.y);
            currentPosition = nextPosition;
        }

        // Add a blue ball in front of the menuItems vector
        sf::CircleShape newBall(20.f);
        newBall.setPosition(0.f, currentPosition.y);
        newBall.setFillColor(sf::Color::White);
        menuItems_.insert(menuItems_.begin(), newBall);
    }
};

class Balls : public Object {
   protected:
    bool ifBomb_;

   public:
    Balls(const sf::Vector2f& size_, const sf::Vector2f& position_, sf::Color color_, bool ifBomb)
        : Object(size_, position_, color_), ifBomb_(ifBomb) {}

    bool getifBomb() const {
        return ifBomb_;
    };
};

class Bomb : public Balls {
   protected:
    std::vector<bool> destructions_;

   public:
    Bomb(const sf::Vector2f& size_, const sf::Vector2f& position_, sf::Color color_, bool ifBomb_, std::vector<bool> destructions_)
        : Balls(size_, position_, color_, ifBomb_), destructions_(destructions_) {}

    std::vector<bool> getDestruction() const;
    void setDestruction(std::vector<bool> destructions){};
};


int main()
{
    // Initialize the Game_Wall object
    Game_Wall gameWall;

    int ilosc_rzedow = 15;

    // Add initial rows of balls
    for (int row = 0; row < ilosc_rzedow; row++)
    {
        gameWall.addNewRow(row);
    }


    // Initialize SFML window with the width and height from Game_Wall
    sf::RenderWindow window(sf::VideoMode(gameWall.width * 45, gameWall.height * 45), "Gierka");

    // Create a red line shape
    sf::RectangleShape redLine(sf::Vector2f(gameWall.width * 45.f, 20.f));
    redLine.setFillColor(sf::Color::Red);
    redLine.setPosition(0.f, 1300.f);

    sf::RectangleShape blackLine(sf::Vector2f(gameWall.width * 45.f, 5.f));
    blackLine.setFillColor(sf::Color::Black);
    blackLine.setPosition(0.f, 1450.f);

    // sf::Font font;
    // if (!font.loadFromFile("arial.ttf")) {
    //     // Failed to load font
    //     return -1;
    // }

    // sf::Text scoreText;
    // scoreText.setFont(font);
    // scoreText.setCharacterSize(24);
    // scoreText.setFillColor(sf::Color::White);
    // scoreText.setPosition(window.getSize().x - 100, window.getSize().y - 30);

    // Create an instance of Game_menu
    Game_menu gameMenu;

    // Initialize menuItems_
    gameMenu.addMenu();

    // Add a new ball
    gameMenu.addNewBall();

    // Add a new ball
    gameMenu.addNewBall();

    // Add a new ball
    gameMenu.addNewBall();


    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color(240, 220, 180));

        // Draw the grid
        for (int row = 0; row < ilosc_rzedow; row++)
        {
            for (int col = 0; col < gameWall.width; col++)
            {
                // Draw the ball
                window.draw(*gameWall.wall_[row][col]);
            }
        }

        // Draw the red line
        window.draw(redLine);

        // Draw the black line
        window.draw(blackLine);

        // // Draw the score text
        // window.draw(scoreText);

        // Draw the accumulated balls from menuItems_
        for (const auto& ball : gameMenu.menuItems_)
        {
            window.draw(ball);
        }

        // Draw the accumulated balls from dowystrzalu
        for (const auto& ball : gameMenu.dowystrzalu)
        {
            window.draw(ball);
        }

        // Display the window
        window.display();
    }

    return 0;
}