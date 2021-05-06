#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bat.h"

class Ball {
    const int width=1366, height=768;
    float speedX=0.8, speedY=-0.8;
    int radius = 10;
    sf::CircleShape ball;
    public:
        Ball();
        void moveBall();
        void resetPosition();
        void checkBoundry(Bat &red, Bat &blue, sf::Sound &sound);
        void drawTo(sf::RenderWindow &window);
};