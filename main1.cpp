#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Ball Explosion");

    // Create the black ball shape
    sf::CircleShape ballShape(40.f);
    ballShape.setFillColor(sf::Color::Black);
    ballShape.setPosition(window.getSize().x / 2.f - ballShape.getRadius(), window.getSize().y / 2.f - ballShape.getRadius());

    // Timer variables
    sf::Clock clock;
    sf::Time explosionTimer;

    // Animation variables
    bool isAnimating = false;
    bool isBallClicked = false;
    float explosionSpeed = 1.5f;



    // Load the destruction texture
    sf::Texture destructionTexture;
    if (!destructionTexture.loadFromFile("textures/explosion.png"))
    {
        std::cerr << "Failed to load destruction.png" << std::endl;
        return 1;
    }

    // Load the bomb texture
    sf::Texture bombTexture;
    if (!bombTexture.loadFromFile("textures/bomb.png"))
    {
        std::cerr << "Failed to load bomb.png" << std::endl;
        return 1;
    }

    // Create the destruction sprite
    sf::Sprite destructionSprite(destructionTexture);
    destructionSprite.setOrigin(destructionTexture.getSize().x / 2.f, destructionTexture.getSize().y / 2.f);
    destructionSprite.setScale(0.2f, 0.2f);
    destructionSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // Create the bomb sprite
    sf::Sprite bombSprite(bombTexture);
    bombSprite.setOrigin(bombTexture.getSize().x / 2.f, bombTexture.getSize().y / 2.f);
    bombSprite.setScale(0.2f, 0.2f);
    bombSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse button pressed: check if ball is clicked
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

                if (ballShape.getGlobalBounds().contains(worldPosition))
                {
                    isBallClicked = true;
                    explosionTimer = sf::Time::Zero;
                }
            }
        }

        // Calculate the elapsed time
        float deltaTime = clock.restart().asSeconds();

        // Check if 2 seconds have passed
        if (isBallClicked && !isAnimating)
        {
            explosionTimer += sf::seconds(deltaTime);
            if (explosionTimer >= sf::seconds(1.f))
            {
                isAnimating = true;
                explosionTimer = sf::Time::Zero;
            }
        }

        // Update the animation if it's in progress
        if (isAnimating)
        {
            // Expand and fade the ball
            ballShape.scale(explosionSpeed * deltaTime, explosionSpeed * deltaTime);
            ballShape.setFillColor(sf::Color(ballShape.getFillColor().r, ballShape.getFillColor().g, ballShape.getFillColor().b, ballShape.getFillColor().a - static_cast<sf::Uint8>(explosionSpeed * deltaTime * 255)));


            // If the ball is no longer visible, close the window
            if (ballShape.getFillColor().a <= 0)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the destruction sprite if 0.2 seconds have passed
        if (explosionTimer >= sf::seconds(0.1f) && explosionTimer < sf::seconds(0.65f))
        {
            window.draw(destructionSprite);
        }
        // Draw the bomb sprite if 0.2 seconds have passed
        else if (explosionTimer >= sf::seconds(0.65f) && explosionTimer < sf::seconds(1.0f))
        {
            window.draw(bombSprite);
        }
        else
        {
            // Draw the black ball shape
            window.draw(ballShape);
        }

        // Display the contents of the window
        window.display();
    }

    return 0;
}