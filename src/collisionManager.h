#pragma once

#include "GameObjects/ball.h"
#include "GameObjects/bricks.h"
#include "GameObjects/paddle.h"

namespace game
{
bool getBallToPaddCollision(Ball& ball, Paddle paddle);
void checkBallToBrickCollision(Ball& ball, Brick brick[quantY][quantX], int& activeBricks);
}