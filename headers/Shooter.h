#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

class Shooter {
    const int width = 1366, height = 768;
    sf::RectangleShape player;
    sf::Texture playerTexture;
    int pHeight;
    float speed = 1;

    public:
        int score=0, dir;
        Shooter(){}
        void setShooter(std::string, int, int);
        void move();
        int getX();
        int getY();
        sf::FloatRect globalBounds();
        void checkBoundry();
        void drawTo(sf::RenderWindow& window);
};

