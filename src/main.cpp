#include"SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include "Ball/ball.h"

using namespace game;

int main()
{
    Ball ball;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Daniela Gonzalez");
    sf::Clock clock;

    initBall(ball, 800, 500);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        updateBall(ball, dt);
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(ball.sprite);
        window.display();
    }

    return 0;    
}