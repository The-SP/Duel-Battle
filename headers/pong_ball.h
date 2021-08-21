#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "pong_bat.h"

class Ball {
    float speedX=0.8*10, speedY=-0.8*10; // initial motion(right, up)
    int radius = 10;
    sf::CircleShape ball;

    float totalTime = 0.f;

public:
    bool isMoving = false;
    Ball();
    void pauseBall(float deltaTime);
    void moveBall();
    void resetPosition();
    void checkBoundry(Bat &red, Bat &blue, sf::Sound &sound);
    void drawTo(sf::RenderWindow &window);
};