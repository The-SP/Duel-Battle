#include "Shooter.h"
#include <iostream>
#include <string>

void Shooter::setShooter(std::string imgFile, int xPos, int direction) {
    dir = direction; //up or down i.e 1 or -1
    player.setSize(sf::Vector2f(75, 75));
    if (!playerTexture.loadFromFile(imgFile)) 
        throw("ERR, failed to load image file");
    player.setTexture(&playerTexture);
    player.setPosition(xPos, 768/2);
    pHeight = playerTexture.getSize().y;
}

void Shooter::move() {
    player.move(0, dir*speed);
}

void Shooter::drawTo(sf::RenderWindow& window) {
    window.draw(player);
}

int Shooter::getX() {
    return player.getPosition().x;
}

int Shooter::getY() {
    return player.getPosition().y;
}

sf::FloatRect Shooter::globalBounds() {
    return player.getGlobalBounds();
}

void Shooter::checkBoundry() {
    int y = getY();
    if (y < 0)
        dir *= -1;
    if (y > height-pHeight)
        dir *= -1;
}