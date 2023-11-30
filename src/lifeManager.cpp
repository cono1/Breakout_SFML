#include "lifeManager.h"

namespace game
{
void decreasePlayerLife(int& life)
{
	if (life > 0)
		life--;
	else
		life = 0;
}
}