#include "Background.h"

WindowBackground::WindowBackground(std::string imageFile) {
    background.setSize(sf::Vector2f(width, height));
    if (!texture.loadFromFile(imageFile))
        throw("ERR, Failed to load image file");  
    background.setTexture(&texture);
}

void WindowBackground::drawTo(sf::RenderWindow &window) {
    window.draw(background);
}

TextMessage::TextMessage() {
    if (!font.loadFromFile("arial.ttf"))
        throw ("ERR, Failed to load font file");
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(25); 
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold | sf::Text::Italic);
}

void TextMessage::changeString(std::string strMessage) {
    text.setString(strMessage);
    text.setOrigin(text.getLocalBounds().width/2, 0);
    text.setPosition(originX, 0);
}

void TextMessage::drawTo(sf::RenderWindow &window) {
    window.draw(text);
}

SoundManager::SoundManager() {
    // load Punch Sound to buffer
    if (!buffer.loadFromFile("./sound/punch.wav"))
        throw("ERR, cant load sound");
    sound.setBuffer(buffer);
    // Background Music
    if (!music.openFromFile("./sound/aot.ogg"))
        throw("ERR, cant open music file");
    music.play();
    music.setVolume(50);
    music.setLoop(true);
}

void SoundManager::playPunchSound() {
    sound.play();
}

void checkGameOver(int redScore, int blueScore)
{
    if (redScore == 3)
        winner = "Red won!";
    if (blueScore == 3)
        winner = "Blue won!";
    if (winner != "None")
        gameOver = true;
}

// void resetGame(Bat& red, Bat& blue, SoundManager& gameSounds) {
//     gameStarted = false;
//     gameOver = false;
//     red.score = 0;
//     blue.score = 0;
//     winner = "None";
//     gameSounds.playPunchSound();
// }