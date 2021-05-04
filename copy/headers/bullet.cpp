#include "bullet.h"
#include <iostream>

Bullet::Bullet(sf::Color color) {
    bullet.setSize(sf::Vector2f(50, 30));
    if (!bulletTexture.loadFromFile("./images/fire.png"))
        throw("ERR, Failed to load image file");  
    bullet.setTexture(&bulletTexture);
}

void Bullet::fire(float speed) {
    bullet.move(speed, 0);
    if (bullet.getPosition().x > width)
        isFiring = false;
}

void Bullet::setPos(sf::Vector2f newPos) {
    bullet.setPosition(newPos);
}

void Bullet::drawTo(sf::RenderWindow &window) {
    window.draw(bullet);
}

void Bullet::checkCollision(Shooter &playerBlock, Shooter &enemyBlock, SoundManager &gameSounds) {
    if (bullet.getGlobalBounds().intersects(enemyBlock.globalBounds())) {
        isFiring = false;
        playerBlock.score++;
        gameSounds.playPunchSound();
    }
    if (bullet.getPosition().x>width || bullet.getPosition().x<0) {
        isFiring = false;
    }
}