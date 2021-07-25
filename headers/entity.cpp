#include "entity.h"

void SpriteEntity::drawTo(sf::RenderWindow& window) {
	window.draw(sprite);
}

void RectEntity::drawTo(sf::RenderWindow& window) {
	window.draw(shape);
}