#include "run_player.h"
#include "run_enemy.h"
#include "initUI.h"
#include <iostream>

class Jungle : private InitUI {
    Player player;
    Enemy enemy;
    InitUI text;
    sf::Text jungleRunScoreText;

    float bgX, bgX2; // 0 and WIDTH
    sf::Texture scrollingBG1, scrollingBG2;
    sf::RectangleShape bg1, bg2;
    sf::Texture gameStateTexture[3];
    sf::RectangleShape gameStateRect[3];

    enum playerTurn {RED_RUNNER, BLUE_RUNNER};
    int playerTurnIndex = 0;
    std::string playerTurnScoreText[2] = {"Red Score: ", "Blue Score: "};
    sf::Color playerColor[2] = {sf::Color::Red, sf::Color::Blue};

    bool gameDraw = false;

public:
    bool bothPlayed = false;
    int runnerScore[2] = {0};

private:
    void scrollBackground();

public:
    Jungle();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void resetJungleRun();
};