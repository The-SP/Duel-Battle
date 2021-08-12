#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class InitUI {
protected:
	sf::Font font;
    void initText(sf::Text& text, const std::string& strMessage, int characterSize, int positionY);
	void initTexture(sf::RectangleShape& rect, sf::Texture& texture, const sf::Vector2f& size, const std::string& imageFile);
};

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