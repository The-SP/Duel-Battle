#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Plane {
    sf::RectangleShape plane;
    sf::Texture planeTexture;
    float speed = 0.5*6;

public:
    static int currentSpaceBackgroundIndex;

public:
    int score = 0;
    Plane();
    void resetPlane(int xPos);
    void move(int dir);
    sf::FloatRect globalBounds();
    void checkBoundry(int resetXPos, sf::Sound &sound);
    void drawTo(sf::RenderWindow& window);
};