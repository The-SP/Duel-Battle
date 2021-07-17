#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "pong_bat.h"

class Ball {
    float speedX=0.8, speedY=-0.8; // initial motion(right, down)
    int radius = 10;
    sf::CircleShape ball;
    public:
        Ball();
        void moveBall();
        void resetPosition();
        void checkBoundry(Bat &red, Bat &blue, sf::Sound &sound);
        void drawTo(sf::RenderWindow &window);
};