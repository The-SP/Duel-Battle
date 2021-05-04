#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>

class Shooter {
    sf::RectangleShape player;
    sf::Texture playerTexture;
    int pHeight, pWidth;

    public:
        int score=0, dir;
        Shooter(std::string, int, int);
        void move();
        int getX();
        int getY();
        sf::FloatRect globalBounds();
        void checkBoundry();
        void drawTo(sf::RenderWindow& window);
};

