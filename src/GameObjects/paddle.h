#pragma once
 
#include "SFML/Graphics.hpp"

namespace game
{
struct Paddle
{
	float x;
	float y;
	float width;
	float height;
	float speed;
	sf::Texture texture;
	sf::Sprite sprite;
};

void initPaddle(Paddle& paddle, float wWidth, float wHeight);
void updatePaddle(Paddle& paddle, float windowWidth, sf::Time dt);
void clearPaddle(Paddle& paddle);
}