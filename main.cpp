#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>

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
    Game()
        : black(sf::Color(0, 0, 0)),
          red(sf::Color(209, 109, 106)),
          green(sf::Color(157, 194, 132)),
          blue(sf::Color(120, 157, 229)),
          yellow(sf::Color(222, 207, 105)),
          violet(sf::Color(139, 125, 190)),
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
        : sf::CircleShape(size_.x) {
        position_x_ = position_.x;
        position_y_ = position_.y;
        setColor(color_);
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

class Game_wall {
   private:
    std::vector<std::vector<Object*> > wall_;

   public:
    void addNewRow(){
        // write a function
    };
};
class Game_menu {
   private:
    std::vector<Object*> menuItems_;

   public:
    void addNewRandomBall(){};
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

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 1680), "My window");

    // Create an sf::CircleShape object
    float radius = 10.0f;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(400.0f, 300.0f);

    // Create a vector of vectors of Object pointers
    std::vector<std::vector<Object*> > wall_;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(240, 220, 180));
        window.draw(circle);
        window.display();
    }

    return 0;
}