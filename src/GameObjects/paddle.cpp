#include "paddle.h"

#include <iostream>

namespace game
{
void movePaddleRight(Paddle& paddle, sf::Time dt);
void movePaddleLeft(Paddle& paddle, sf::Time dt);

void initPaddle(Paddle& paddle, float wWidth, float wHeight)
{
	paddle.x = wWidth / 2;
	paddle.y = wHeight - 50;
	paddle.width = 0.5f;
	paddle.height = 0.1f;
	paddle.speed = 400;

	if (!paddle.texture.loadFromFile("res/padd.jpg"))
		std::cout << "failed to open paddle image";
	paddle.sprite.setTexture(paddle.texture);
	paddle.sprite.setPosition(paddle.x, paddle.y);
	paddle.sprite.setScale(sf::Vector2f(paddle.width, paddle.height));
}

void updatePaddle(Paddle& paddle, float windowWidth, sf::Time dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.x > 0)
	{
		movePaddleLeft(paddle, dt);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.x + (paddle.sprite.getGlobalBounds().width) < windowWidth)
	{
		movePaddleRight(paddle, dt);
	}
	paddle.sprite.setPosition(paddle.x, paddle.y);
}

void movePaddleRight(Paddle& paddle, sf::Time dt)
{
	paddle.x += static_cast<float>(paddle.speed) * dt.asSeconds();
}

void movePaddleLeft(Paddle& paddle, sf::Time dt)
{
	paddle.x -= static_cast<float>(paddle.speed) * dt.asSeconds();
}

void clearPaddle(Paddle& paddle)
{
	paddle.width = 0;
	paddle.height = 0;

	paddle.sprite.scale(paddle.width, paddle.height);
}
}