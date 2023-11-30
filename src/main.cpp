#include"SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

#include "GameObjects/ball.h"
#include "GameObjects/bricks.h"
#include "GameObjects/paddle.h"

using namespace game;

int main()
{
    Ball ball;
    Brick bricks[quantY][quantX];
    Paddle paddle;

    const int windowWidth = 1024;
    const int windowHeight = 768;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Daniela Gonzalez");
    sf::Clock clock;

    srand(time(NULL));
    initBall(ball, 800, 500);
    initBrick(bricks);
    initPaddle(paddle, windowWidth , windowHeight);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        updateBall(ball, dt);
        updatePaddle(paddle, windowWidth, dt);
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        window.clear();
        for (int i = 0; i < quantY; i++)
        {
            for (int j = 0; j < quantX; j++)
            {
                window.draw(bricks[i][j].rect);
            }
        }
        window.draw(paddle.sprite);
        window.draw(ball.sprite);
        window.display();
    }

    return 0;    
}