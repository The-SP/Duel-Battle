#include "bat.h"

Bat::Bat() {
    bat.setSize(sf::Vector2f(16, 100));
    bat.setOrigin(bat.getLocalBounds().width/2, bat.getLocalBounds().height/2);
    bat.setOutlineThickness(-1.f);
    bat.setOutlineColor(sf::Color::White);
}

void Bat::setBat(sf::Color colorName, int positionX) {
    bat.setPosition(positionX, height/2);
    bat.setFillColor(colorName);
}

void Bat::moveBat(int dir) {
    bat.move(0, dir*speed);
}

sf::FloatRect Bat::globalBounds() {
    return bat.getGlobalBounds();
}

void Bat::drawTo(sf::RenderWindow &window) {
    window.draw(bat);
}