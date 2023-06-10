#include "classes.h"
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

using namespace std;




int main()
{

    //Class objects inicialization
    Game_wall objects_wall(40,33);

    //Game_menu with inicialization with 8 balls in queue
    Game_menu objects_menu(8);
    //Game_menu with inicialization with score starting from 0
    Game game(0);

    //Setting resolution of the screen
    game.setResolution();

    //Loading all of the objects in game - wall of balls , menu of balls , lines ,arrow etc.
    game.start(objects_wall, objects_menu);

    sf::RenderWindow window(sf::VideoMode(1800/int(game.getResolution()), 1680/int(game.getResolution())), "Ball Shooter Game");


    //Making program run in 60 FPS
    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Checking if mouse wass clicked to shoot a ball
            game.shootIfClicked(objects_menu, window, event);
        }
        //Setting Frame rate to 60 frames persecond
        sf::Time elapsed = clock.restart();
        game.FPS(clock, timePerFrame, elapsed);

        //function that controls whole game for player
        game.game_play(objects_wall, objects_menu, window, elapsed, clock);

        // Clear the window
        window.clear(sf::Color(240, 220, 180));

        //displaying whole game
        game.dis(objects_wall, objects_menu, window);

        // Display the window
        window.display();
    }

    return 0;

}
