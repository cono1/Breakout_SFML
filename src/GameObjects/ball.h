#pragma once

#include"SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"

namespace game
{
struct Ball
{
	float x;
	float y;
	float dirX;
	float dirY;
	float speedX;
	float speedY;
	sf::Texture texture;
	sf::Sprite sprite;
};

void initBall(Ball& ball, float x, float y);
void updateBall(Ball& ball, sf::Time dt, int wWidth, int wHeight);
void restartBall(Ball& ball, float x, float y);
}