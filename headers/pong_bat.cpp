#include "pong_bat.h"
#include "global.h"

Bat::Bat() {
    bat.setSize(sf::Vector2f(16, 100));
    bat.setOrigin(bat.getLocalBounds().width/2, bat.getLocalBounds().height/2);
    bat.setOutlineThickness(-1.f);
    bat.setOutlineColor(sf::Color::White);
}

void Bat::setBat(sf::Color colorName, int positionX) {
    bat.setPosition(positionX, HEIGHT/2);
    bat.setFillColor(colorName);
}

void Bat::checkBoundry() {
    if (bat.getPosition().y + bat.getSize().y/2 > HEIGHT)
        bat.setPosition(bat.getPosition().x, HEIGHT-bat.getSize().y/2);
    else if (bat.getPosition().y - bat.getSize().y/2 < 0)
        bat.setPosition(bat.getPosition().x, bat.getSize().y/2);
}

void Bat::moveBat(int dir) {
    bat.move(0, dir*speed);
    checkBoundry();
}

sf::FloatRect Bat::globalBounds() {
    return bat.getGlobalBounds();
}

void Bat::drawTo(sf::RenderWindow &window) {
    window.draw(bat);
}