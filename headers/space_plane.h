#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string.h>

class Plane {
    const int width=1366, height=768; // direct assigning value instead of passing as argument when required . find a way to inherit these data from a class or properly pass
    sf::RectangleShape player;
    sf::Texture playerTexture;
    float speed = 0.5;

    public:
        int score = 0;
        Plane();
        void setPlanePos(int xPos);
        void move(int dir);
        int getY();
        sf::FloatRect globalBounds();
        void checkBoundry(int resetXPos, sf::Sound &sound);
        void drawTo(sf::RenderWindow& window);
};