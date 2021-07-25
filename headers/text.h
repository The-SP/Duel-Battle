#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class TextMessage {
	static float totalTime, switchTime;

public:
    static void initText(const sf::Font& font, sf::Text& text, std::string strMessage, int characterSize, int positionY);
	static void blink(sf::Text& text, float deltaTime);
};