#include "initUI.h"
#include "global.h"

void InitUI::initText(sf::Text& text, const std::string& strMessage, int characterSize, int positionY) {
    text.setFont(font);
    text.setString(strMessage);
    text.setCharacterSize(characterSize); 
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(WIDTH/2, positionY);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Italic);
}

void InitUI::initTexture(sf::RectangleShape& rect, sf::Texture& texture, const sf::Vector2f& size, const std::string& imageFile) {
    rect.setSize(size);
    if (!texture.loadFromFile(imageFile))
        throw("ERR, Failed to load image file");  
    rect.setTexture(&texture);
    rect.setPosition(WIDTH/2-rect.getSize().x/2, HEIGHT/2-rect.getSize().y/2);   
    if (rect.getSize().x == 700) { // add border only for instructions cards (card has width 700)
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(3.f);
    }
}

// float InitUI::totalTime = 0.f;
// float InitUI::switchTime = 0.03f;

// void InitUI::blink(sf::Text& text, float deltaTime)
// {
// 	totalTime += deltaTime;
// 	if (totalTime >= switchTime) {
// 		totalTime -= switchTime;
// 		text.setOutlineColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
// 	}
// }
