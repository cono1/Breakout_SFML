#include "ball.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

int offset = 10;

namespace game
{
void checkBallLimits(Ball& ball, int wWidth, int wHeight);

void initBall(Ball& ball, float x, float y)
{
	ball.dirX = static_cast<float>(rand() % 300 - 150);
	ball.dirY = -100.f;
	ball.x = x;
	ball.y = y + offset;
	ball.speedX = 3.0f;
	ball.speedY = 3.0f;
	if (!ball.texture.loadFromFile("res/ball.png"))
	{
		std::cout << "failed to open image";
	}
	ball.sprite.setTexture(ball.texture);
	ball.sprite.setPosition(ball.x, ball.y);
	ball.sprite.setScale(sf::Vector2f(0.2f, 0.2f));
}

void updateBall(Ball& ball, sf::Time dt, int wWidth, int wHeight)
{
	checkBallLimits(ball, wWidth, wHeight);

	ball.x += static_cast<float>(ball.dirX * ball.speedX * dt.asSeconds());
	ball.y -= static_cast<float>(ball.dirY * ball.speedY * dt.asSeconds());
	ball.sprite.setPosition(ball.x, ball.y);
}

void restartBall(Ball& ball, float x, float y)
{
	ball.dirX = static_cast<float>(rand() % 300 - 150);
	ball.dirY = -100.f;
	ball.x = x;
	ball.y = y + offset;
}

void checkBallLimits(Ball& ball, int wWidth, int wHeight)
{
	if (ball.x < 0 || ball.x + ball.sprite.getGlobalBounds().width >= wWidth)
	{
		if (ball.x < 0)
			ball.x += ball.sprite.getGlobalBounds().width / 2;

		if (ball.x + ball.sprite.getGlobalBounds().width >= wWidth)
			ball.x -= ball.sprite.getGlobalBounds().width;

		ball.dirX *= -1.f;
	}

	if (ball.y + ball.sprite.getGlobalBounds().width < 0) 
	{
		ball.y += ball.sprite.getGlobalBounds().width;
		ball.dirY *= -1.f;
	}
}

void clearBall(Ball& ball)
{
	ball.sprite.scale(0, 0);
	ball.sprite.setPosition(0, 0);
}
}