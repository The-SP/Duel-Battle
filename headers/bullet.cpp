#include "bullet.h"
#include <iostream>

void Bullet::setBullet() {
    bullet.setSize(sf::Vector2f(75, 50));
    if (!bulletTexture.loadFromFile("./images/fire.png"))
        throw("ERR, Failed to load image file");  
    bullet.setTexture(&bulletTexture);
}

void Bullet::fire(float speed) {
    bullet.move(speed, 0);
}

void Bullet::setPos(sf::Vector2f newPos) {
    bullet.setPosition(newPos);
}

void Bullet::drawTo(sf::RenderWindow &window) {
    window.draw(bullet);
}

void Bullet::checkCollision(Shooter &playerBlock, Shooter &enemyBlock, sf::Sound &sound, int width) {
    if (bullet.getGlobalBounds().intersects(enemyBlock.globalBounds())) {
        isFiring = false;
        playerBlock.score++;
        sound.play();
    }
    if (bullet.getPosition().x>width || bullet.getPosition().x<0) {
        isFiring = false;
    }
}