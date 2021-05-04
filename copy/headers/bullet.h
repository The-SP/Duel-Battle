#pragma once
#include "global.h"
#include "Shooter.h"
#include "Background.h"
#include <SFML/Graphics.hpp>

class Bullet {
    private:
        sf::RectangleShape bullet;
        sf::Texture bulletTexture;
    
    public:
        bool isFiring;
        Bullet(sf::Color);
        void fire(float speed);
        void setPos(sf::Vector2f);
        void drawTo(sf::RenderWindow& window);
        void checkCollision(Shooter& , Shooter&, SoundManager&);
};