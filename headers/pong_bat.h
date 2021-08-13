#pragma once
#include <SFML/Graphics.hpp>


class Bat {
    float speed = 0.8*10;
    sf::RectangleShape bat;
    void checkBoundry();

public: 
    int score = 0;
    Bat();
    void setBat(sf::Color color, int positionX);
    void moveBat(int dir);
    sf::FloatRect globalBounds();
    void drawTo(sf::RenderWindow &window);
};