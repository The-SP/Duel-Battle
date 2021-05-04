#pragma once
#include "Shooter.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bullet {
    private:
        sf::RectangleShape bullet;
        sf::Texture bulletTexture;
    
    public:
        bool isFiring=false;
        Bullet(){}
        void setBullet();
        void fire(float speed);
        void setPos(sf::Vector2f);
        void drawTo(sf::RenderWindow& window);
        void checkCollision(Shooter& , Shooter&, sf::Sound&, int width);
};