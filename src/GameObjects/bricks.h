#pragma once
#include "SFML/Graphics.hpp"

namespace game
{
	const int quantX = 14;
	const int quantY = 6;

struct Brick
{
	sf::RectangleShape rect;
	bool isActive;
	float x;
	float y;
	float width;
	float height;
	float r;
	float g;
	float b;
};

void initBrick(Brick brick[quantY][quantX]);
void deactiveBrick(Brick brick[quantY][quantX], int posX, int posY, int& activeBricksLeft);
void clearBricks(Brick brick[quantY][quantX]);
}