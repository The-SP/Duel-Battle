#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class InitUI {
	// static float totalTime, switchTime;
protected:
	sf::Font font;

    void initText(sf::Text& text, const std::string& strMessage, int characterSize, int positionY);
	void initTexture(sf::RectangleShape& rect, sf::Texture& texture, const sf::Vector2f& size, const std::string& imageFile);
	// void blink(sf::Text& text, float deltaTime);
};