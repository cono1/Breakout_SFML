#include "bricks.h"

namespace game
{
void initBrick(Brick brick[quantY][quantX])
{
	int firstBrickYPosition = 10;
	int space = 10;

	for (int i = 0; i < quantY; i++)
	{
		for (int j = 0; j < quantX; j++)
		{
			brick[i][j].width = 60.f;
			brick[i][j].height = 35.5f;
			brick[i][j].x = j * (brick[i][j].width + space) + brick[i][j].width / 2;
			brick[i][j].y = i * (brick[i][j].height + space) + firstBrickYPosition;
			brick[i][j].isActive = true;
			brick[i][j].r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.5 + 0.5 * 255;
			brick[i][j].g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX * 4.0) * 255;
			brick[i][j].b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX * 2.0) * 255;

			brick[i][j].rect.setSize(sf::Vector2f(brick[i][j].width, brick[i][j].height));
			brick[i][j].rect.setPosition(sf::Vector2f(brick[i][j].x, brick[i][j].y));
			brick[i][j].rect.setFillColor(sf::Color(brick[i][j].r, brick[i][j].g, brick[i][j].b));

		}
	}
}

void deactiveBrick(Brick brick[quantY][quantX], int posX, int posY, int& activeBricksLeft)
{
	if (brick[posX][posY].isActive)
	{
		brick[posX][posY].isActive = false;
		activeBricksLeft--;
	}

	if (!brick[posX][posY].isActive)
	{
		brick[posX][posY].width = 0;
		brick[posX][posY].height = 0;
		brick[posX][posY].rect.setSize(sf::Vector2f(brick[posX][posY].width, brick[posX][posY].height));
	}
}

void clearBricks(Brick brick[quantY][quantX])
{
	for (int i = 0; i < quantY; i++)
	{
		for (int j = 0; j < quantX; j++)
		{
			brick[i][j].width = 0.0f;
			brick[i][j].height = 0.0f;
			brick[i][j].isActive = false;

			brick[i][j].rect.setSize(sf::Vector2f(brick[i][j].width, brick[i][j].height));
		}
	}
}
}