#include "asteroid.h"

Asteroid::Asteroid() {
    if (rand()%2 == 0)
        dir = 1; // asteroid moves right
    else    
         dir = -1; // moves left
    asteroid.setRadius(radius);
    asteroid.setPosition(getRandomPosition()); 
    asteroid.setFillColor(sf::Color::White);
}

sf::Vector2f Asteroid::getRandomPosition() {
    int x = rand() % width;
    int y = rand() % (height-200);
    return sf::Vector2f(x,y);
}

void Asteroid::drawTo(sf::RenderWindow &window) {
    window.draw(asteroid);
}

void Asteroid::move() {
    asteroid.move(dir*speed, 0);
    checkBoundry();
}

void Asteroid::checkBoundry() {
    // Left boundry
    if (asteroid.getPosition().x < -100) {
        asteroid.setPosition(width-100, getRandomPosition().y);
    }
    // Right boundry
    if (asteroid.getPosition().x > width+100) {
        asteroid.setPosition(0, getRandomPosition().y);
    }
}