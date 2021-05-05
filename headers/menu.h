#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "./Shooter.h"
#include "./bullet.h"
#include "./plane.h"
#include "./asteroid.h"
#include <iostream>
#include <string.h>

class Game {
    private:
        unsigned int width, height;
        sf::RenderWindow window;
        // Text
        sf::Font font;
        sf::Text scoreMessage, winnerMessage, playInstructions;
        // Background
        sf::Texture shooterTexture, raceTexture, resultTexture;
        sf::RectangleShape shooterBackground, raceBackground, resultBackground;
        // Sound effects
        sf::Sound sound;
        sf::SoundBuffer buffer;
        sf::Music music;
        // Shooter and bullet
        Shooter redShooter, blueShooter;
        Bullet redBullet, blueBullet;
        // Plane
        Plane redPlane, bluePlane;
        sf::RectangleShape spaceRaceBoundry;
        // Asteroid
        Asteroid asteroid[30];

        bool gameOver = false;
        std::string winner = "None";
        int gameNumber = 0; //0=shooter, 1=racer
        int redOverallScore = 0, blueOverallScore = 0;

    public: 
        Game();
        void setText(sf::Text& text, std::string strMessage, int characterSize, int positionY);
        void setSound();
        void run();
        void shooterGame();
        void spaceRace();
        void resultPage();
        void checkGameOver(int redScore, int blueScore);
        void resetGame();
};