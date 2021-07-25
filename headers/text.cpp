#include "text.h"
#include "global.h"

void TextMessage::initText(const sf::Font& font, sf::Text& text, std::string strMessage, int characterSize, int positionY) {
    text.setFont(font);
    text.setString(strMessage);
    text.setCharacterSize(characterSize); 
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(WIDTH/2, positionY);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Italic);
}

float TextMessage::totalTime = 0.f;
float TextMessage::switchTime = 0.03f;

void TextMessage::blink(sf::Text& text, float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		text.setOutlineColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
	}
}
