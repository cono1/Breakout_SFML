#include"SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include "GameObjects/ball.h"
#include "GameObjects/bricks.h"

using namespace game;

int main()
{
    Ball ball;
    Brick bricks[quantY][quantX];

    sf::RenderWindow window(sf::VideoMode(1024, 768), "Daniela Gonzalez");
    sf::Clock clock;

    srand(time(NULL));
    initBall(ball, 800, 500);
    initBrick(bricks);

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
        for (int i = 0; i < quantY; i++)
        {
            for (int j = 0; j < quantX; j++)
            {
                window.draw(bricks[i][j].rect);
            }
        }
        window.display();
    }

    return 0;    
}