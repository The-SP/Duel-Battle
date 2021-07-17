#pragma once
#include <SFML/Graphics.hpp>


class Bat {
    float speed = 0.8;
    sf::RectangleShape bat;

    public: 
        int score = 0;
        Bat();
        void setBat(sf::Color color, int positionX);
        void moveBat(int dir);
        sf::FloatRect globalBounds();
        void drawTo(sf::RenderWindow &window);
};