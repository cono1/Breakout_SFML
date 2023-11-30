#include "ball.h"

#include <iostream>
#include <time.h>
#include <cmath>
#include <cstdlib>

int offset = 10;

namespace game
{
void initBall(Ball& ball, float x, float y)
{
	ball.dirX = static_cast<float>(rand() % 300 - 150);
	ball.dirY = 100.f;
	ball.x = x;
	ball.y = y + offset;
	ball.speedX = 1.0f;
	ball.speedY = 1.0f;
	if (!ball.texture.loadFromFile("res/ball.png"))
	{
		std::cout << "failed to open image";
	}
	ball.sprite.setTexture(ball.texture);
	ball.sprite.setPosition(ball.x, ball.y);
	ball.sprite.setScale(sf::Vector2f(0.2f, 0.2f));
}

void updateBall(Ball& ball, sf::Time dt)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//{
	ball.x += static_cast<float>(ball.dirX * ball.speedX * dt.asSeconds());
	ball.y -= static_cast<float>(ball.dirY * ball.speedY * dt.asSeconds());
	ball.sprite.setPosition(ball.x, ball.y);
	//}
}

void drawBall(Ball ball)
{
	//slSprite(ball.texture, ball.x, ball.y, ball.width, ball.height);
}

void restartBall(Ball& ball, float x, float y)
{
	srand(time(NULL));
	ball.dirX = static_cast<float>(rand() % 300 - 150);
	ball.dirY = 100.f;
	ball.x = x;
	ball.y = y + offset;
}
}