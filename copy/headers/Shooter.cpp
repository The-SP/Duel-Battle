#include "Shooter.h"
#include "global.h"
#include <iostream>
#include <string>

Shooter::Shooter(std::string imgFile, int xPos, int direction) {
    dir = direction;
    player.setSize(sf::Vector2f(50, 50));
    if (!playerTexture.loadFromFile(imgFile)) 
        std::cerr << "Error loading image\n";
    player.setTexture(&playerTexture);
    player.setPosition(xPos, originY);
    pHeight = playerTexture.getSize().y;
    pWidth = playerTexture.getSize().x;
}

void Shooter::move() {
    player.move(0, dir*speed);
    checkBoundry();
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