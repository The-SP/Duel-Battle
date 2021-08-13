#include "space_asteroid.h"
#include "global.h"

Asteroid::Asteroid() {
    if (rand()%2 == 0)
        dir = 1; // asteroid moves right
    else    
         dir = -1; // moves left
    asteroid.setRadius(10+rand()%5);
    asteroid.setPosition(getRandomPosition()); 
}

void Asteroid::initTexture(const sf::Texture& texture) {
    asteroid.setTexture(&texture);
}

sf::Vector2f Asteroid::getRandomPosition() {
    int x = rand() % WIDTH;
    int y = rand() % (HEIGHT-200);
    return sf::Vector2f(x,y);
}

void Asteroid::drawTo(sf::RenderWindow &window) {
    window.draw(asteroid);
}

void Asteroid::move() {
    asteroid.move(dir*speed, 0);
    asteroid.rotate(dir*0.5f); // rotation effect while moving
    checkBoundry();
}

void Asteroid::checkBoundry() {
    // Left boundry
    if (asteroid.getPosition().x < -100) {
        asteroid.setPosition(WIDTH-100, getRandomPosition().y);
    }
    // Right boundry
    if (asteroid.getPosition().x > WIDTH+100) {
        asteroid.setPosition(0, getRandomPosition().y);
    }
}

void Asteroid::checkCollision(Plane &redPlane, Plane &bluePlane, sf::Sound &sound) {
    if (asteroid.getGlobalBounds().intersects(redPlane.globalBounds())) {
        redPlane.resetPlane(WIDTH/2-100);
        sound.play();
    }
    if (asteroid.getGlobalBounds().intersects(bluePlane.globalBounds())) {
        bluePlane.resetPlane(WIDTH/2+100);
        sound.play();
    }
}