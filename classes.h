
#ifndef CLASSES_H
#define CLASSES_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <iterator>
#include <string>

class Game_wall;
class Game_menu;

class Game
{
private:
    int score_;
    float resOfScreen;

    sf::Texture arrowTexture;
    sf::Sprite arrow;
    sf::RectangleShape redLine;
    sf::RectangleShape blackLine;

    sf::Vector2f velocityOfBall;

    int index_x_;
    int index_y_;

    //Variables for game animations
    std::vector<sf::Vector2f> positionBomb_;
    std::vector<sf::Vector2f> positionBall_;
    bool detonation_;
    sf::Texture bombTexture_;
    sf::Texture explosionTexture_;
    sf::Time explosionTimer_;

public:
    Game(int score_);

    int getScore() const;

    void setScore(int score);

    void setResolution();


    float getResolution();


    void initiateArrow();

    void initiateDectructionTextures();

    //Building red a nd balck line in the two funcitons below
    void initiateRedLine(float resolution);

    void initiateBlackLine(float resolution);

    void arrowDisplay(sf::RenderWindow &window);

    void scoreDisplay(sf::RenderWindow &window);

    void FPS(sf::Clock &clock, sf::Time &timePerFrame, sf::Time &elapsed);

    void addPositionBall(sf::Vector2f position);

    void addPositionBomb(sf::Vector2f position);

    void shootIfClicked(Game_menu &objects_menu, sf::RenderWindow &window, sf::Event &event);

    void moveShotBall (sf::Time &elapsed, Game_menu &objects_menu);

    void borderColision(sf::RenderWindow &window, Game_menu &objects_menu);

    bool ballColision(sf::RenderWindow &window, Game_menu &objects_menu , Game_wall &objects_wall);

    void touchingRedLine(sf::RenderWindow &window, Game_menu &objects_menu , Game_wall &objects_wall);

    void bombDetonate(Game_wall &objects_wall, int index_x, int index_y);

    void destruction(Game_wall& objects_wall, int index_x, int index_y, int destructionCount);

    void animate(sf::RenderWindow &window);

    void start(Game_wall &objects_wall, Game_menu &objects_menu);

    void game_play(Game_wall &objects_wall, Game_menu &objects_menu, sf::RenderWindow &window, sf::Time &elapsed, sf::Clock &clock);

    void dis(Game_wall &objects_wall, Game_menu &objects_menu, sf::RenderWindow &window);
};

class Object : public sf::CircleShape {
protected:
    sf::Vector2f position_;
    sf::Color color_;

public:
    Object(const sf::Vector2f &size_, const sf::Vector2f &position_, sf::Color color_);

    sf::Vector2f getPosition() const;

    void setPosition(const sf::Vector2f &position);

    int getSize() const;

    void setSize(int size);

    sf::Color getColor() const;

    void setColor(sf::Color color);
};

class Balls : public Object
{
protected:
    bool ifBomb_;


public:
    Balls(const sf::Vector2f &size_, const sf::Vector2f &position_, sf::Color color_, bool ifBomb);

    bool getifBomb() const;

};

class Bomb : public Balls
{
protected:
    sf::Sprite ballSprite;
    int nrOfDetonation;

public:
    Bomb(const sf::Vector2f &size_, const sf::Vector2f &position_, sf::Color color_, bool ifBomb_, sf::Sprite ballSprite ,int nrOfDetonation);

    sf::Sprite getDesctructions();

    int getNrOfDetonation();
};

class Game_wall
{
private:
    friend class Game;
    std::vector<std::vector<Object *> > wall_;
    int width_;
    int height_;
    std::vector<sf::Texture> textures_;
    sf::Sprite ballSprite_;

public:
    Game_wall(const int width, const int height);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    void initializeWall();

    int random_num();

    std::vector<sf::Texture> texture();

    void setTexture();

    //Function crating new row at the top each move or during game creation
    void addNewRow(int score , float resOfScreen);
    //Function moves rows of balls a one row down
    void moveWall(float resOfScreen);

};

class Game_menu
{
private:
    friend class Game;
    std::vector<Object* > menu_;
    int numOfBalls_;

public:
    Game_menu(int numOfBalls);

    void initializeMenu();

    int getNumOfBalls();

    int random_ball(int a,int b);

    //Function adds new ball to queue
    void addNewBall(int score, float resOfScreen);
    //Function moves balls one move forward.
    void  moveMenu(float resOfScreen);

};


#endif // CLASSES_H
