#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "./bat.h"
#include "./ball.h"
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
        sf::Text title, howToPlay, scoreText, winnerText, nextGameText;
        // Background
        sf::Texture homeTexture, pongTexture, shooterTexture, raceTexture;
        sf::RectangleShape homeBackground, pongBackground, shooterBackground, raceBackground;
        // Sound effects
        sf::Sound sound;
        sf::SoundBuffer buffer;
        sf::Music music;

        // PingPong
        Bat redBat, blueBat;
        Ball ball;
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
        int gameNumber = 0;//0=home, 1=pingpong, 2=shooter, 3=racer
        int redFinalScore = 0, blueFinalScore = 0;

    public: 
        Game();
        void setText(sf::Text& text, std::string strMessage, int characterSize, int positionY);
        void setSound();
        void run();
        void homePage();
        void endPage();
        void pingPong();
        void shooterGame();
        void spaceRace();
        void resultPage(sf::RectangleShape &background);
        void selectMenuOption(sf::Text &text);
        void checkGameOver(int redScore, int blueScore);
        void resetGame();
};