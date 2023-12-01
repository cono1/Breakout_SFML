#pragma once

#include "SFML/Graphics.hpp"

namespace game
{
    struct MenuRect
    {
        int x;
        int y;
        float width;
        float height;
        float initWidth;
        float maxWidth;
        sf::RectangleShape rect;
    };

void initBackButton(MenuRect& pauseRect);
void drawBackButton(MenuRect& pauseRect, sf::RenderWindow& window);
}