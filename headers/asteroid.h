#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Asteroid {
    unsigned int width=1366, height=768; // direct assigning value instead of passing as argument when required . find a way to inherit these data from a class or properly pass
    int radius = 10;
    int dir;
    float speed = 0.5;
    sf::CircleShape asteroid;

    public:
        Asteroid();
        void drawTo(sf::RenderWindow &window);
        void move();
        void checkBoundry();
        sf::Vector2f getRandomPosition();
};
