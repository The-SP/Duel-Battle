#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "space_plane.h"

class Asteroid {
    int radius = 10;
    int dir;
    float speed = 0.5;
    sf::CircleShape asteroid;

private:
    void checkBoundry();
    sf::Vector2f getRandomPosition();

public:
    Asteroid();
    void move();
    void checkCollision(Plane &redPlane, Plane &bluePlane, sf::Sound &sound);
    void drawTo(sf::RenderWindow &window);
};
