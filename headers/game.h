#pragma once
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include "pong_bat.h"
#include "pong_ball.h"
#include "space_plane.h"
#include "space_asteroid.h"
#include "global.h"
#include "./Shooter.h"
#include "./bullet.h"


class Game {
private:
    sf::RenderWindow window;
    // Text
    sf::Font font;
    sf::Text title1, title2, scoreText, winnerText;
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
    // Space Race
    Plane redPlane, bluePlane;
    sf::RectangleShape spaceRaceBoundry;
    Asteroid asteroid[40];
    // Shooter and bullet
    Shooter redShooter, blueShooter;
    // Bullet redBullet, blueBullet;

    bool showHowToPlay = true;
    bool gameOver = false;
    std::string winner = "None";
    int gameNumber = 0;//0=home, 1=pingpong, 2=space race, 3=jungle run 4=endPage
    int redFinalScore = 0, blueFinalScore = 0;

    float deltaTime;
    bool buttonPressedEvent = false;
    // how to play
    sf::Texture howToTexture[4];
    sf::RectangleShape howToRect[4];
    sf::RectangleShape playButton;
    sf::Texture buttonTexture[2];

private: 
    void initText(sf::Text& text, std::string strMessage, int characterSize, int positionY);
    void setSound();

    // Pages
    void homePage();
    void howToPlayPage(sf::RectangleShape &background);
    void resultPage(sf::RectangleShape &background);
    void endPage();
    void pingPong();
    void jungleRun();
    void spaceRace();
    void checkGameOver(int redScore, int blueScore);
    void resetGame();

    // Menu
    bool isButtonSelected(sf::RectangleShape& button);
    void initTexture(sf::RectangleShape& rect, sf::Texture& texture, const sf::Vector2f& size, const std::string& imageFile);

public:
    Game();
    void run();
};