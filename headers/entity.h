#pragma once
#include <SFML/Graphics.hpp>

class SpriteEntity {
protected:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	void drawTo(sf::RenderWindow& window);
};

class RectEntity {
protected:
	sf::RectangleShape shape;
	sf::Texture rectTexture;
	int objectWidth, objectHeight;
public:
	void drawTo(sf::RenderWindow& window);
};

class AnimationEntity {
protected:
	sf::IntRect uvRect;
	int objectWidth, objectHeight;
	int imageNo = 0, rowNo = 0;
	float switchTime, totalTime = 0.f;
	float speed;
};