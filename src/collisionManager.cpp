#include "collisionManager.h"

namespace game
{
bool getBallToPaddCollision(Ball& ball, Paddle paddle)
{
    return (paddle.x + (paddle.sprite.getGlobalBounds().width) >= ball.x &&
            paddle.y + (paddle.sprite.getGlobalBounds().height) >= ball.y &&
            paddle.x <= ball.x + ball.sprite.getGlobalBounds().width &&
            paddle.y <= ball.y + ball.sprite.getGlobalBounds().height);
}

void checkBallToBrickCollision(Ball& ball, Brick brick[quantY][quantX], int& activeBricks)
{
    for (int i = 0; i < quantY; i++)
    {
        for (int j = 0; j < quantX; j++)
        {
            if (brick[i][j].x + brick[i][j].width >= ball.x &&
                brick[i][j].y + brick[i][j].height >= ball.y &&
                brick[i][j].x <= ball.x + ball.sprite.getGlobalBounds().width &&
                brick[i][j].y <= ball.y + ball.sprite.getGlobalBounds().height)
            {
                if (brick[i][j].isActive)
                {
                    deactiveBrick(brick, i, j, activeBricks);
                    ball.dirX *= -1;
                    ball.dirY *= -1;
                    return;
                }
            }

        }
    }
}
}