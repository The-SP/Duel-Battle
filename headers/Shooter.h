#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

class Shooter {
    sf::RectangleShape player;
    sf::Texture playerTexture;
    int pHeight, pWidth;
    float speed = 0.8;

    public:
        int score=0, dir;
        Shooter(){}
        void setShooter(std::string, int, int);
        void move();
        int getX();
        int getY();
        sf::FloatRect globalBounds();
        void checkBoundry(int height);
        void drawTo(sf::RenderWindow& window);
};

