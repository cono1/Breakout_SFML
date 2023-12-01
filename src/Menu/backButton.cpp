#include "backButton.h"

namespace game
{
void initBackButton(MenuRect& pauseRect)
{
	pauseRect.rect.setFillColor(sf::Color::Red);
	pauseRect.rect.setPosition(950, 30);
	pauseRect.rect.setSize(sf::Vector2f(35, 35));
	pauseRect.initWidth = pauseRect.rect.getSize().x;
	pauseRect.maxWidth = pauseRect.rect.getSize().x + 10;

   pauseRect.width = 35;
   pauseRect.height = 35;
   pauseRect.x = 950;
   pauseRect.y = 30;
   pauseRect.initWidth = pauseRect.width;
   pauseRect.maxWidth = pauseRect.width + 10;
   pauseRect.rect.setFillColor(sf::Color::Red);
   pauseRect.rect.setSize(sf::Vector2f(pauseRect.width, pauseRect.height));
   pauseRect.rect.setPosition(pauseRect.x, pauseRect.y);
}

void drawBackButton(MenuRect& pauseRect, sf::RenderWindow& window)
{
	window.draw(pauseRect.rect);
}
}