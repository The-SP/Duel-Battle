#include "space_plane.h"
#include "global.h"

int Plane::currentSpaceBackgroundIndex = 0;

Plane::Plane() {
    player.setSize(sf::Vector2f(30, 60));
    if (!playerTexture.loadFromFile("./images/plane.png")) 
        throw("ERR, failed to load image file");
    player.setTexture(&playerTexture);
}

void Plane::setPlanePos(int xPos) {
    player.setPosition(xPos, HEIGHT-100);
}

void Plane::move(int dir) {
    player.move(0, dir*speed);
}

void Plane::drawTo(sf::RenderWindow& window) {
    window.draw(player);
}

int Plane::getY() {
    return player.getPosition().y;
}

sf::FloatRect Plane::globalBounds() {
    return player.getGlobalBounds();
}

void Plane::checkBoundry(int resetXPos, sf::Sound &sound) {
    int y = getY();
    if (y+50 < 0) {
        setPlanePos(resetXPos);
        score++;
        currentSpaceBackgroundIndex = (currentSpaceBackgroundIndex == 0) ? 1 : 0;
        sound.play();
    }
}