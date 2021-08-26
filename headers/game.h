#pragma once
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "pong_bat.h"
#include "pong_ball.h"
#include "space_plane.h"
#include "space_asteroid.h"
#include "run_Jungle.h"
#include "global.h"


class Game : private InitUI {
private:
    sf::RenderWindow window;
    float deltaTime, totalTime = 0.f;

    // Text
    sf::Font scoreFont;
    sf::Text title1, title2, scoreText, winnerText;
    // Background
    sf::Texture homeTexture, pongTexture, spaceTexture[2], jungleTexture, resutlTexture;
    sf::RectangleShape homeBackground, pongBackground, spaceBackground[2], jungleBackground, resultBackground;
    // Sound effects
    sf::Sound sound, pongSound, raceSound, cheerSound;
    sf::SoundBuffer buffer, pongBuffer, raceBuffer, cheerBuffer;
    sf::Music music;

    // PingPong
    Bat redBat, blueBat;
    Ball ball;
    // Space Race
    Plane redPlane, bluePlane;
    sf::RectangleShape spaceRaceBoundry;
    Asteroid asteroid[25];
    int asteroidSize = 25;
    sf::Texture asteroidTexture[3];
    // Jungle Run
    Jungle jungle;

    // Game state handling
    int gameNumber = 0; //0=home, 1=pingpong, 2=space race, 3=jungle run 4=result
    enum gameName {HOME_INDEX, PING_PONG, SPACE_RACE, JUNGLE_RUN, RESULT_INDEX};
    bool showHowToPlay = true;
    bool gameOver = false;
    std::string winner = "None";
    int redFinalScore = 0, blueFinalScore = 0;

    // how to play
    sf::Texture howToTexture[4];
    sf::RectangleShape howToRect[4];
    // Play Button
    bool buttonPressedEvent = false;
    sf::RectangleShape playButton;
    sf::Texture buttonTexture[2];

private: 
    void initSound();
    // Menu
    bool isButtonSelected(sf::RectangleShape& button);
    void textBlink(sf::Text& text, float deltaTime, float switchTime = 0.2f);

    // Pages
    void homePage();
    void howToPlayPage(sf::RectangleShape &background);
    void resultPage(sf::RectangleShape &background);
    void endPage();
    // Games
    void pingPong();
    void spaceRace();
    void jungleRun();
    // Game state handling
    void checkGameOver(int redScore, int blueScore);
    void checkGameOver(char winnerColor);
    void resetGame();

public:
    Game();
    void run();
};