#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "global.h"
#include <string>
#include <iostream>

class WindowBackground {
    private:
        sf::RectangleShape background;
        sf::Texture texture;
    
    public:
        WindowBackground(std::string imageFile);
        void drawTo(sf::RenderWindow &window);
};

class TextMessage {
    sf::Text text;
    sf::Font font;

    public:
        TextMessage();
        void changeString(std::string strMessage);
        void drawTo(sf::RenderWindow &window);
};

class SoundManager {
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::Music music;
    
    public:
        SoundManager();
        void playPunchSound();
};

void checkGameOver(int redScore, int blueScore);