#include "classes.h"

Game::Game(int score_) : score_(score_) {}

int Game::getScore() const
{
    return score_;
}
void Game::setScore(int score)
{
    score_ = score;
}

void Game::setResolution(){
    std::string resolution;
    std::cout<<"Game resolution 4K or FullHD enter in which you want to play:"<<std::endl;
    std::cin>>resolution;
    if (resolution=="4k" || resolution=="4K"){
        resOfScreen=1;
    }
    else{
        resOfScreen=2;
    }
}

float Game::getResolution(){
    return resOfScreen;
}

void Game::initiateArrow(){
    if (!arrowTexture.loadFromFile("textures/arrow.png")) {
        std::cout << "Texture ARROW fail to load" << std::endl;
    }

    arrow.setTexture(arrowTexture);
    sf::Vector2f scale(1/resOfScreen, 1/resOfScreen);
    arrow.setScale(scale);
    arrow.setOrigin(arrow.getLocalBounds().width / 2.f, arrow.getLocalBounds().height);
    arrow.setPosition(900/resOfScreen, 1472.f/resOfScreen);
    arrow.setRotation(0);
}

void Game::initiateDectructionTextures(){
    if (!explosionTexture_.loadFromFile("textures/explosion.png"))
    {
        std::cout << "Failed to load explosion.png" << std::endl;
    }

    sf::Texture bombTexture;
    if (!bombTexture_.loadFromFile("textures/bomb.png"))
    {
        std::cout << "Failed to load bomb.png" << std::endl;
    }
}

//Building red a nd balck line in the two funcitons below
void Game::initiateRedLine(float resolution){
    redLine.setSize((sf::Vector2f(1800.f/resolution, 10.f/resolution)));
    redLine.setFillColor(sf::Color::Red);
    redLine.setPosition(0.f, 1390.f/resolution);
}

void Game::initiateBlackLine(float resolution){
    blackLine.setSize((sf::Vector2f(1800.f/resolution, 10.f/resolution)));
    blackLine.setFillColor(sf::Color::Black);
    blackLine.setPosition(0.f, 1550.f/resolution);
}

void Game::arrowDisplay(sf::RenderWindow &window){
    sf::Vector2i cursorPosition = sf::Mouse::getPosition(window);

    float dx = cursorPosition.x - arrow.getPosition().x;
    float dy = cursorPosition.y - arrow.getPosition().y;
    float angleRad = std::atan2(dy, dx) * 180 / M_PI;

    arrow.setRotation(angleRad + 90);

    window.draw(arrow);
}

void Game::scoreDisplay(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("Fonts/font.ttf");

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("SCORE:  " + std::to_string(score_));
    scoreText.setCharacterSize(60/resOfScreen);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(1500/resOfScreen, 1580/resOfScreen);

    window.draw(scoreText);
}

void Game::FPS(sf::Clock &clock, sf::Time &timePerFrame, sf::Time &elapsed){


    // Limit the frame rate to 60 FPS
    if (elapsed < timePerFrame)
    {
        sf::sleep(timePerFrame - elapsed);
        elapsed = timePerFrame;
    }
}

void Game::addPositionBall(sf::Vector2f position) {
    if (std::find(positionBall_.begin(), positionBall_.end(), position) == positionBall_.end()) {
        positionBall_.push_back(position);
    }
}
void Game::addPositionBomb(sf::Vector2f position){
    if (std::find(positionBomb_.begin(), positionBomb_.end(), position) == positionBomb_.end()){
        positionBomb_.push_back(position);
    }
}



std::vector<sf::Color> vec_color()
{
    std::vector<sf::Color> vec_color_ ;
    vec_color_.push_back(sf::Color(0, 0, 0));
    vec_color_.push_back(sf::Color(209, 109, 106));
    vec_color_.push_back(sf::Color(157, 194, 132));
    vec_color_.push_back(sf::Color(120, 157, 229));
    vec_color_.push_back(sf::Color(244, 140, 251));
    vec_color_.push_back(sf::Color(175,175,175));
    vec_color_.push_back(sf::Color(107, 34, 70));
    return vec_color_;
}

Object::Object(const sf::Vector2f &size_, const sf::Vector2f &position_, sf::Color color_)
    : sf::CircleShape(size_.x), position_(position_)
{
    setFillColor(color_); // Set the fill color of the circle shape
    setPosition(position_); // Set the position of the circle shape
}

sf::Vector2f Object::getPosition() const
{
    return position_;
}

void Object::setPosition(const sf::Vector2f &position)
{
    position_ = position;
    sf::CircleShape::setPosition(position); // Set the position of the circle shape
}

int Object::getSize() const
{
    return static_cast<int>(getRadius());
}

void Object::setSize(int size)
{
    setRadius(static_cast<float>(size));
}

sf::Color Object::getColor() const
{
    return color_;
}

void Object::setColor(sf::Color color)
{
    color_ = color;
    setFillColor(color_); // Set the fill color of the circle shape
}

Balls::Balls(const sf::Vector2f &size_, const sf::Vector2f &position_, sf::Color color_, bool ifBomb)
    : Object(size_, position_, color_), ifBomb_(ifBomb) {}

bool Balls::getifBomb() const
{
    return ifBomb_;
}

Bomb::Bomb(const sf::Vector2f &size_, const sf::Vector2f &position_, sf::Color color_, bool ifBomb_, sf::Sprite ballSprite ,int nrOfDetonation)
    : Balls(size_, position_, color_, ifBomb_), ballSprite(ballSprite), nrOfDetonation(nrOfDetonation) {}

sf::Sprite Bomb::getDesctructions(){
    return ballSprite;
}

int Bomb::getNrOfDetonation(){
    return nrOfDetonation;
}

Game_wall::Game_wall(const int width, const int height)
    : width_(width), height_(height)
{
    initializeWall();
}

int Game_wall::getWidth() const
{
    return width_;
}
void Game_wall::setWidth(int width) {
    width_=width;
}
int Game_wall::getHeight() const
{
    return height_;
}
void Game_wall::setHeight(int height){
    height_=height;
}

void Game_wall::initializeWall()
{
    wall_ = std::vector<std::vector<Object *> >(height_, std::vector<Object *>(width_, nullptr));
}
int Game_wall::random_num()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 100);
    return dis(gen);
}

std::vector<sf::Texture> Game_wall::texture()
{
    std::vector<sf::Texture> textures;
    sf::Texture vertical;
    if (!vertical.loadFromFile("textures/vertical.png")) {
        std::cout << "Texture VERTICAL fail to load" << std::endl;
    }
    textures.push_back(vertical);

    sf::Texture horizontal;
    if (!horizontal.loadFromFile("textures/horizontal.png")) {
        std::cout << "Texture HORIZONTAL fail to load" << std::endl;
    }
    textures.push_back(horizontal);

    sf::Texture cross;
    if (!cross.loadFromFile("textures/cross.png")) {
        std::cout << "Texture Cross fail to load" << std::endl;
    }
    textures.push_back(cross);

    return textures;
}

void Game_wall::setTexture(){
    textures_ = texture();
}



//Function crating new row at the top each move or during game creation
void Game_wall::addNewRow(int score , float resOfScreen)
{
    std::vector<Object *> line;
    std::srand(std::time(0));
    std::vector<sf::Color> vec_colors = vec_color();

    //making as many balls as with as possible and inserting them to vector line

    for (int i = 0; i < width_; i++)
    {
        int random_number = random_num();
        int player_score = score;
        float initialStartPoint_y = 0;
        // cheching if i is not a first ball
        sf::Color previousColor ;
        if (i > 0)
        {
            previousColor = line[i - 1]->getColor();

        }
        else
        {
            previousColor = vec_colors[(std::rand() % 3) + 1];
        }


        if (previousColor == vec_colors[0])
        {
            previousColor = vec_colors[1];
        }

        int randomDestruciton = (std::rand() % 3);
        //Special condition for different levels in game 50, 150, and third level for more than 150 points
        if (player_score < 150)
        {
            if (random_number <= 25)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f(((i) * 45.f)/resOfScreen, initialStartPoint_y), previousColor, false);
                line.push_back(ball);
            }
            else if (random_number <= 40)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[1], false);
                line.push_back(ball);
            }
            else if (random_number <= 68)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[2], false);
                line.push_back(ball);
            }
            else if (random_number <= 93)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[3], false);
                line.push_back(ball);
            }
            else
            {

                ballSprite_.setTexture(textures_[randomDestruciton]);
                ballSprite_.setScale(0.5f/resOfScreen, 0.5f/resOfScreen);
                Bomb *bomb = new Bomb(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[0], true, ballSprite_, randomDestruciton);

                line.push_back(bomb);
            }
        }
        else if (player_score < 350 && player_score >=150)
        {
            if (random_number <= 35)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), previousColor, false);
                line.push_back(ball);
            }
            else if (random_number <= 50)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[1], false);
                line.push_back(ball);
            }
            else if (random_number <= 65)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[2], false);
                line.push_back(ball);
            }
            else if (random_number <= 80)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[3], false);
                line.push_back(ball);
            }
            else if (random_number <= 95)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[4], false);
                line.push_back(ball);
            }
            else
            {
                ballSprite_.setTexture(textures_[randomDestruciton]);
                ballSprite_.setScale(0.5f/resOfScreen, 0.5f/resOfScreen);
                Bomb *bomb = new Bomb(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[0], true, ballSprite_, randomDestruciton);

                line.push_back(bomb);
            }
        }
        else
        {
            if (random_number <= 45)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), previousColor, false);
                line.push_back(ball);
            }
            else if (random_number <= 55)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[1], false);
                line.push_back(ball);
            }
            else if (random_number <= 65)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[2], false);
                line.push_back(ball);
            }
            else if (random_number <= 75)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[3], false);
                line.push_back(ball);
            }
            else if (random_number <= 85)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[4], false);
                line.push_back(ball);
            }
            else if (random_number <= 95)
            {
                Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i + 1) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[5], false);
                line.push_back(ball);
            }
            else
            {
                ballSprite_.setTexture(textures_[randomDestruciton]);
                ballSprite_.setScale(0.5f/resOfScreen, 0.5f/resOfScreen);
                Bomb *bomb = new Bomb(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f((i) * 45.f/resOfScreen, initialStartPoint_y), vec_colors[0], true, ballSprite_, randomDestruciton);

                line.push_back(bomb);
            }
        }
    }
    // Pushing line made of balls to final wall_ vector
    for (int i = 0; i < width_; i++)
    {
        wall_[0][i] = line[i];
    }

}
//Function moves rows of balls a one row down
void Game_wall::moveWall(float resOfScreen)
{
    for (int i = height_ - 2; i >= 0; i--)
    {
        for (int j = 0; j < width_; j++)
        {
            if (wall_[i][j] != nullptr)
            {
                std::swap(wall_[i][j], wall_[i + 1][j]);
                if (wall_[i + 1][j] != nullptr)
                {
                    sf::Vector2f new_position(j * 45.f/resOfScreen, (i + 1) * 45.f/resOfScreen);
                    wall_[i + 1][j]->setPosition(new_position);
                }
            }
        }
    }
}


Game_menu::Game_menu(int numOfBalls): numOfBalls_(numOfBalls){
    initializeMenu();
}

void Game_menu::initializeMenu()
{
    menu_ = std::vector<Object *> (numOfBalls_);
}

int Game_menu::getNumOfBalls(){
    return numOfBalls_;
}

int Game_menu::random_ball(int a,int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(a, b);
    return dis(gen);
}
//Function adds new ball to queue
void Game_menu::addNewBall(int score, float resOfScreen){
    std::vector<sf::Color> vec_colors = vec_color();
    if (score<150){
        Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f(44.f/resOfScreen, 1600.f/resOfScreen), vec_colors[random_ball(1,3)], false);
        menu_[0]=ball;
    }
    else if(score < 350 && score >=150){
        Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f(44.f/resOfScreen, 1600.f/resOfScreen), vec_colors[random_ball(1,4)], false);
        menu_[0]=ball;
    }
    else{
        Balls *ball = new Balls(sf::Vector2f(20.f/resOfScreen, 20.f/resOfScreen), sf::Vector2f(44.f/resOfScreen, 1600.f/resOfScreen), vec_colors[random_ball(1,5)], false);
        menu_[0]=ball;
    }
}
//Function moves balls one move forward.
void  Game_menu::moveMenu(float resOfScreen){

    //Moving balls one by one forward to it's final shooting destination
    for (int i = numOfBalls_- 2 ; i >= 0; i--)
    {
        if (i<numOfBalls_- 2){
            if (menu_[i]!= nullptr)
            {
                std::swap(menu_[i], menu_[i + 1]);
                if (menu_[i + 1] != nullptr)
                {
                    sf::Vector2f new_position( (((i+1) * 90.f)+45.f)/resOfScreen, 1600.f/resOfScreen);
                    menu_[i + 1]->setPosition(new_position);
                }
            }
        }
        //special condition for final ball to change its normal position to up and center.
        else if (i==(numOfBalls_- 2)){
            if (menu_[i]!= nullptr)
            {
                std::swap(menu_[i], menu_[i + 1]);
                if (menu_[i + 1] != nullptr)
                {
                    sf::Vector2f new_position( 878.f/resOfScreen, 1450.f/resOfScreen);
                    menu_[i + 1]->setPosition(new_position);
                }
            }

        }
    }
}

void Game::shootIfClicked(Game_menu &objects_menu, sf::RenderWindow &window, sf::Event &event) {
    // Checking if mouse was pressed. If so, setting velocity at which ball will move
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (objects_menu.menu_[objects_menu.getNumOfBalls()-1] != nullptr) {

            //Checking if position chnaged to not change path of ball to new when mouse clicked accidentaly twice
            sf::Vector2f positionOfBall = objects_menu.menu_[objects_menu.getNumOfBalls()-1]->getPosition();
            if(positionOfBall.x==878.f/resOfScreen && positionOfBall.y ==1450.f/resOfScreen) {
                sf::Vector2f displacement(mousePosition.x - positionOfBall.x, mousePosition.y - positionOfBall.y);
                float distance = std::sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
                float speed = 430.0f/resOfScreen;
                velocityOfBall = displacement / distance * speed;
            }
        }
    }
}

void Game::moveShotBall (sf::Time &elapsed, Game_menu &objects_menu){
    //calculating time in seconds to retreive it's destination
    float dtAsSeconds = elapsed.asSeconds();
    if (objects_menu.menu_[objects_menu.getNumOfBalls()-1]!=nullptr){
        sf::Vector2f position=objects_menu.menu_[objects_menu.getNumOfBalls()-1]->getPosition();

        position+=velocityOfBall * dtAsSeconds;
        objects_menu.menu_[objects_menu.getNumOfBalls()-1]->setPosition(position);
    }
}

void Game::borderColision(sf::RenderWindow &window, Game_menu &objects_menu){
    if (objects_menu.menu_[objects_menu.getNumOfBalls()-1]!=nullptr){
        sf::Vector2u windowSize = window.getSize();
        float radius= objects_menu.menu_[objects_menu.getNumOfBalls()-1]->getSize();
        sf::Vector2f positionOfBall = objects_menu.menu_[objects_menu.getNumOfBalls()-1]->getPosition();

        if (positionOfBall.x  < 0) // Left border collision
        {
            positionOfBall.x = radius;
            velocityOfBall.x = -velocityOfBall.x;
        }
        else if (positionOfBall.x + radius > windowSize.x) // Right border collision
        {
            positionOfBall.x = windowSize.x - radius;
            velocityOfBall.x = -velocityOfBall.x;
        }

        if (positionOfBall.y - radius < 0) // Top border collision
        {
            positionOfBall.y = radius;
            velocityOfBall.y = -velocityOfBall.y;
        }
        else if (positionOfBall.y + radius > windowSize.y) // Bottom border collision
        {
            positionOfBall.y = windowSize.y - radius;
            velocityOfBall.y = -velocityOfBall.y;
        }
    }

}

bool Game::ballColision(sf::RenderWindow& window, Game_menu& objects_menu, Game_wall& objects_wall) {
    if (objects_menu.menu_[objects_menu.getNumOfBalls() - 1] != nullptr) {
        for (int i = 0; i < objects_wall.height_; i++) {
            for (int j = 0; j < objects_wall.width_; j++) {
                if (objects_wall.wall_[i][j] != nullptr) {
                    //Checking here if they collide
                    sf::Vector2f position1 = objects_menu.menu_[objects_menu.getNumOfBalls() - 1]->getPosition();
                    sf::Vector2f position2 = objects_wall.wall_[i][j]->getPosition();
                    float radius1 = objects_menu.menu_[objects_menu.getNumOfBalls() - 1]->getSize();
                    float radius2 = objects_wall.wall_[i][j]->getSize();

                    // Calculate the distance between the centers of the circles
                    float dx = position2.x - position1.x;
                    float dy = position2.y - position1.y;
                    float distance = std::sqrt(dx * dx + dy * dy);

                    // Check if the circles are colliding
                    if (distance <= radius1 + radius2) {
                        if (position1.x < position2.x - radius2) { // left
                            sf::Vector2f new_position((j - 1) * 45.f / resOfScreen, (i) * 45.f / resOfScreen);
                            objects_menu.menu_[objects_menu.getNumOfBalls() - 1]->setPosition(new_position);
                            std::swap(objects_menu.menu_[objects_menu.getNumOfBalls() - 1], objects_wall.wall_[i][j - 1]);
                            index_y_=i;
                            index_x_=j-1;
                            return true;
                        }
                        else if (position1.x > position2.x + radius2) { // right
                            sf::Vector2f new_position((j + 1) * 45.f / resOfScreen, (i) * 45.f / resOfScreen);
                            objects_menu.menu_[objects_menu.getNumOfBalls() - 1]->setPosition(new_position);
                            std::swap(objects_menu.menu_[objects_menu.getNumOfBalls() - 1], objects_wall.wall_[i][j + 1]);
                            index_y_=i;
                            index_x_=j+1;
                            return true;
                        }
                        else { // bottom
                            sf::Vector2f new_position(j * 45.f / resOfScreen, (i + 1) * 45.f / resOfScreen);
                            objects_menu.menu_[objects_menu.getNumOfBalls() - 1]->setPosition(new_position);
                            std::swap(objects_menu.menu_[objects_menu.getNumOfBalls() - 1], objects_wall.wall_[i + 1][j]);
                            index_y_=i+1;
                            index_x_=j;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


void Game::touchingRedLine(sf::RenderWindow &window, Game_menu &objects_menu, Game_wall &objects_wall){

    //function checking if any of the balls where behind red line making the game end
    int end=31;
    for (int i = 0; i < objects_wall.height_; i++)
    {
        for (int j = 0; j < objects_wall.width_; j++)
        {
            if (objects_wall.wall_[i][j] != nullptr){
                //printing final score in terminal after the red line is crossed
                if (i==end){
                    window.close();
                    std::cout<<"Congratulations your score: "<<score_<<"!!!"<<std::endl;
                }
            }
        }
    }
}

void Game::bombDetonate(Game_wall &objects_wall, int index_x, int index_y){

    Bomb* bomb = dynamic_cast<Bomb*>(objects_wall.wall_[index_y][index_x]);
    int typeOfBomb = bomb->getNrOfDetonation();
    if (typeOfBomb==0){//vertical
        for(int i=0;i<=30;i++){
            if (objects_wall.wall_[i][index_x]!=nullptr){
                addPositionBall(objects_wall.wall_[i][index_x]->getPosition());
                objects_wall.wall_[i][index_x]=nullptr;
                score_+=1;
            }
        }
    }

    if (typeOfBomb==1){//horizontal
        for(int j=0;j<=39;j++){
            if (objects_wall.wall_[index_y][j]!=nullptr){
                addPositionBall(objects_wall.wall_[index_y][j]->getPosition());
                objects_wall.wall_[index_y][j]=nullptr;
                score_+=1;
            }

        }
    }

    if (typeOfBomb==2){//all directions
        for(int i=0;i<=30;i++){
            if (objects_wall.wall_[i][index_x]!=nullptr){
                addPositionBall(objects_wall.wall_[i][index_x]->getPosition());
                objects_wall.wall_[i][index_x]=nullptr;
                score_+=1;
            }
        }
        for(int j=0;j<=39;j++){
            if (objects_wall.wall_[index_y][j]!=nullptr){
                addPositionBall(objects_wall.wall_[index_y][j]->getPosition());
                objects_wall.wall_[index_y][j]=nullptr;
                score_+=1;
            }
        }
    }
}


// function chaecking and destroing the ball.
void Game::destruction(Game_wall& objects_wall, int index_x, int index_y, int destructionCount) {

    sf::Color main_ball;
    sf::Color ball_left;
    sf::Color ball_right;
    sf::Color ball_bottom;
    sf::Color ball_top;

    if (objects_wall.wall_[index_y][index_x] != nullptr) {
        main_ball = objects_wall.wall_[index_y][index_x]->getFillColor();
    }

    //ball color and destruction check for top side
    if (index_y > 0 && objects_wall.wall_[index_y - 1][index_x] != nullptr) {
        ball_top = objects_wall.wall_[index_y - 1][index_x]->getFillColor();
        if (main_ball == ball_top) {
            destructionCount++;
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }
            destruction(objects_wall, index_x, index_y - 1, destructionCount);
        }
        else if (ball_top==sf::Color::Black){
            if (objects_wall.wall_[index_y-1][index_x] != nullptr) {
                addPositionBomb(objects_wall.wall_[index_y-1][index_x]->getPosition());
            }
            bombDetonate(objects_wall, index_x, index_y-1);

        }
        else if (destructionCount > 0) {
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }
        }
    }

    //ball color and destruction check for  left side
    if (index_x > 0 && objects_wall.wall_[index_y][index_x - 1] != nullptr) {
        ball_left = objects_wall.wall_[index_y][index_x - 1]->getFillColor();
        if (main_ball == ball_left) {

            destructionCount++;
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }
            destruction(objects_wall, index_x - 1, index_y, destructionCount);
        }
        else if (ball_left==sf::Color::Black){
            if (objects_wall.wall_[index_y][index_x-1] != nullptr) {
                addPositionBomb(objects_wall.wall_[index_y][index_x-1]->getPosition());
            }
            bombDetonate(objects_wall, index_x-1, index_y);

        }
        else if (destructionCount > 0) {
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }
        }
    }

    //ball color and destruction check for right side
    if (index_x < 38 && objects_wall.wall_[index_y][index_x + 1] != nullptr) {
        ball_right = objects_wall.wall_[index_y][index_x + 1]->getFillColor();
        if (main_ball == ball_right) {

            destructionCount++;
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }

            destruction(objects_wall, index_x + 1, index_y, destructionCount);
        }
        else if (ball_right==sf::Color::Black){
            if (objects_wall.wall_[index_y][index_x+1] != nullptr) {
                addPositionBomb(objects_wall.wall_[index_y][index_x+1]->getPosition());
            }
            bombDetonate(objects_wall, index_x+1, index_y);

        }
        else if (destructionCount > 0) {
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }
        }

    }

    //ball color and destruction check for bottom side
    if (index_y < 32 && objects_wall.wall_[index_y + 1][index_x] != nullptr) {
        ball_bottom = objects_wall.wall_[index_y + 1][index_x]->getFillColor();
        if (main_ball == ball_bottom) {

            destructionCount++;
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }

            destruction( objects_wall, index_x, index_y + 1,destructionCount);
        }
        else if (ball_bottom==sf::Color::Black){
            if (objects_wall.wall_[index_y+1][index_x] != nullptr) {
                addPositionBomb(objects_wall.wall_[index_y+1][index_x]->getPosition());
            }
            bombDetonate(objects_wall, index_x, index_y+1);

        }
        else if (destructionCount > 0) {
            if (objects_wall.wall_[index_y][index_x] != nullptr) {
                addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
                objects_wall.wall_[index_y][index_x] = nullptr;
                score_+=1;
            }
        }
    }
    else if (destructionCount > 0) {
        if (objects_wall.wall_[index_y][index_x] != nullptr) {
            addPositionBall(objects_wall.wall_[index_y][index_x]->getPosition());
            objects_wall.wall_[index_y][index_x] = nullptr;
            score_+=1;
        }
    }
}

void Game::animate(sf::RenderWindow &window){

    if(detonation_==true){
        if (!positionBomb_.empty()){
            if (explosionTimer_ >= sf::seconds(0.01f) && explosionTimer_ < sf::seconds(0.50f))
            {
                for (int i = 0; i < positionBomb_.size(); i++)
                {
                    sf::Sprite bombSprite(bombTexture_);
                    bombSprite.setOrigin(bombTexture_.getSize().x / 2.f, bombTexture_.getSize().y / 2.f);
                    bombSprite.setScale(0.2f / resOfScreen*((explosionTimer_.asSeconds()-0.01f)/0.50f), 0.2f / resOfScreen*((explosionTimer_.asSeconds()-0.01f)/0.50f));
                    float shakeMagnitude = 1.0f;  // Adjust the magnitude of the shaking effect
                    float offsetX = (std::rand() % 2 == 0 ? -1 : 1) * shakeMagnitude;
                    float offsetY = (std::rand() % 2 == 0 ? -1 : 1) * shakeMagnitude;

                    bombSprite.setPosition(positionBomb_[i].x + (45.0f / 2 / resOfScreen) + offsetX,
                                           positionBomb_[i].y + (45.f / resOfScreen) + (45.0f / 2 / resOfScreen) + offsetY);

                    window.draw(bombSprite);
                }
            }
            else if (explosionTimer_ >= sf::seconds(0.50f) && explosionTimer_ < sf::seconds(1.0f)){
                for (int i=0; i<positionBall_.size();i++){
                    sf::Sprite ballSprite(explosionTexture_);
                    ballSprite.setOrigin(explosionTexture_.getSize().x / 2.f, explosionTexture_.getSize().y / 2.f);
                    ballSprite.setScale(0.15f/resOfScreen*((explosionTimer_.asSeconds()-0.5f)/1.f), 0.15f/resOfScreen*((explosionTimer_.asSeconds()-0.5f)/1.f));
                    ballSprite.setPosition(positionBall_[i].x+(45.0f/2/resOfScreen),positionBall_[i].y+(45.f/resOfScreen)+(45.0f/2/resOfScreen));
                    window.draw(ballSprite);
                }

            }
            else if (explosionTimer_ > sf::seconds(1.0f) ){
                explosionTimer_=sf::Time::Zero;
                positionBomb_.clear();
                positionBall_.clear();
                detonation_=false;
            }
        }
        else{
            if (explosionTimer_ >= sf::seconds(0.001f) && explosionTimer_ < sf::seconds(0.65f))
            {
                for (int i=0; i<positionBall_.size();i++){
                    sf::Sprite ballSprite(explosionTexture_);
                    ballSprite.setOrigin(explosionTexture_.getSize().x / 2.f, explosionTexture_.getSize().y / 2.f);
                    ballSprite.setScale(0.1f/resOfScreen*((explosionTimer_.asSeconds()-0.001f)/0.55f), 0.1f/resOfScreen*((explosionTimer_.asSeconds()-0.001f)/0.55f));
                    ballSprite.setPosition(positionBall_[i].x+(45.0f/2/resOfScreen),positionBall_[i].y+(45.f/resOfScreen)+(45.0f/2/resOfScreen));
                    window.draw(ballSprite);
                }

            }


            else if (explosionTimer_ > sf::seconds(0.65f) ){
                explosionTimer_=sf::Time::Zero;
                positionBomb_.clear();
                positionBall_.clear();
                detonation_=false;
            }
        }

    }
}

//Start func to load all objects on window
void Game::start(Game_wall &objects_wall, Game_menu &objects_menu)
{
    score_=0;

    initiateArrow();
    initiateRedLine(resOfScreen);
    initiateBlackLine(resOfScreen);
    initiateDectructionTextures();

    int ball_start_height = 14;

    //Makeing 2d vector with empty cells
    objects_wall.initializeWall();

    objects_wall.setTexture();
    //loop adding row and moving it lower
    for (int i = 0; i < ball_start_height; i++)
    {
        objects_wall.addNewRow(score_, resOfScreen);
        objects_wall.moveWall(resOfScreen);

    }
    objects_wall.addNewRow(score_,resOfScreen);

    // Making vector withempty cells for balls in queue
    objects_menu.initializeMenu();

    //loop adding ball and moving to shooting position and ther rest after
    for (int i = 1; i <= objects_menu.getNumOfBalls() ; i++){
        objects_menu.addNewBall(score_,resOfScreen);
        objects_menu.moveMenu(resOfScreen);
    }
    objects_menu.addNewBall(score_,resOfScreen);

}

void Game::game_play(Game_wall &objects_wall, Game_menu &objects_menu, sf::RenderWindow &window, sf::Time &elapsed, sf::Clock &clock){

    moveShotBall (elapsed, objects_menu); //Moving ball with desired velocity sotred in velocityOfBall'
    borderColision(window, objects_menu); //Checking for border colision
    if(ballColision(window, objects_menu, objects_wall)){ //Checking for colision with balls on wall and making new move
        sf::Vector2f zero(0.f,0.f);
        velocityOfBall=zero;

        detonation_=false;
        destruction(objects_wall, index_x_, index_y_, 0);
        explosionTimer_ = sf::Time::Zero;

        detonation_=true;

        objects_menu.moveMenu(resOfScreen);
        objects_menu.addNewBall(score_,resOfScreen);
        objects_wall.moveWall(resOfScreen);
        objects_wall.addNewRow(score_, resOfScreen);
        touchingRedLine(window, objects_menu, objects_wall);
    }
    float deltaTime = clock.restart().asSeconds();
    explosionTimer_ += sf::seconds(deltaTime);
}

//Displaying whole game here
void Game::dis(Game_wall &objects_wall, Game_menu &objects_menu, sf::RenderWindow &window)
{
    //RedLine gets dipslayed here
    window.draw(redLine);

    //Arrow gets displayed here
    arrowDisplay(window);

    //BlackLine gets dipslayed here
    window.draw(blackLine);

    //Score display
    scoreDisplay(window);

    //Game wall displayed here
    for (int i = 0; i < objects_wall.getHeight(); i++) {
        for (int j = 0; j < objects_wall.getWidth(); j++) {
            Object *object = objects_wall.wall_[i][j];

            if (object != nullptr) {
                sf::Vector2f position = object->getPosition();

                object->setPosition(position);
                window.draw(*object);

                if (dynamic_cast<Bomb*>(object) != nullptr) {
                    Bomb* bomb = dynamic_cast<Bomb*>(object);
                    sf::Sprite ballSprite = bomb->getDesctructions();
                    position.x += 2.5/resOfScreen;
                    position.y += 2/resOfScreen;
                    ballSprite.setPosition(position);
                    window.draw(ballSprite);
                }
            }

        }
    }

    //Game menu dipsplayed here
    for (int i = 0; i < objects_menu.getNumOfBalls(); i++)
    {
        if (objects_menu.menu_[i] != nullptr)
        {
            window.draw(*(objects_menu.menu_[i]));
        }

    }

    //Animations displayed here
    animate(window);
}
