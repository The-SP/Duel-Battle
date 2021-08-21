#include "space_plane.h"
#include "global.h"

int Plane::currentSpaceBackgroundIndex = 0;

Plane::Plane() {
    plane.setSize(sf::Vector2f(30, 60));
    if (!planeTexture.loadFromFile("./images/plane.png")) 
        throw("ERR, failed to load image file");
    plane.setTexture(&planeTexture);
    plane.setOrigin(sf::Vector2f(30/2, 0));
}

void Plane::resetPlane(int xPos) {
    plane.setPosition(xPos, HEIGHT-100);
}

void Plane::move(int dir) {
    plane.move(0, dir*speed);
}

void Plane::drawTo(sf::RenderWindow& window) {
    window.draw(plane);
}

sf::FloatRect Plane::globalBounds() {
    return plane.getGlobalBounds();
}

void Plane::checkBoundry(int resetXPos, sf::Sound &sound) {
    // Finish line
    if (plane.getPosition().y+50 < 0) {
        resetPlane(resetXPos);
        score++;
        currentSpaceBackgroundIndex = (currentSpaceBackgroundIndex == 0) ? 1 : 0;
        sound.play();
    }

    // below starting line
    if (plane.getPosition().y > HEIGHT-100)
        resetPlane(resetXPos);
}