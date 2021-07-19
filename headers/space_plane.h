#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Plane {
    sf::RectangleShape player;
    sf::Texture playerTexture;
    float speed = 0.5;

public:
    static int currentSpaceBackgroundIndex;

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