#include "run_Jungle.h"
#include "global.h"

Jungle::Jungle() {
    bgX = 0;
    bgX2 = WIDTH;
    bg1.setSize(sf::Vector2f(WIDTH, HEIGHT));
    bg2.setSize(sf::Vector2f(WIDTH, HEIGHT));
    // scrollingBG2 is x-mirror image of scrollingBG1 that makes transition smooth
    if (!scrollingBG1.loadFromFile("./images/jungle/bg1.png") || !scrollingBG2.loadFromFile("./images/jungle/bg2.png"))
        throw("ERR, Failed to load image file");  
    bg1.setTexture(&scrollingBG1);
    bg2.setTexture(&scrollingBG2);

    std::string imageFile[3] = {"images/jungle/red_turn.jpg", "images/jungle/blue_turn.jpg", "images/jungle/score_draw.jpg"};
    initTexture(gameStateRect[0], gameStateTexture[0], sf::Vector2f(700, 400), imageFile[0]);
    initTexture(gameStateRect[1], gameStateTexture[1], sf::Vector2f(700, 400), imageFile[1]);
    initTexture(gameStateRect[2], gameStateTexture[2], sf::Vector2f(700, 400), imageFile[2]);


    // Init Text
    if (!font.loadFromFile("fonts/pixel.ttf"))
        throw("Err, can't load font filel");
    InitUI::initText(jungleRunScoreText, "Red Score: 0", 50, 0);
	jungleRunScoreText.setPosition(WIDTH-175, 0);
    jungleRunScoreText.setOutlineThickness(2);
    jungleRunScoreText.setOutlineColor(playerColor[RED_RUNNER]);
}

void Jungle::scrollBackground() {
    bg1.setPosition(bgX, 0);
    bg2.setPosition(bgX2, 0);
    bgX -= (-SCROLL_SPEED);
    bgX2 -= (-SCROLL_SPEED);
    if (bgX < -WIDTH)
        bgX = WIDTH;
    if (bgX2 < -WIDTH)
        bgX2 = WIDTH;
}

void Jungle::update(float deltaTime) {
    if (gameDraw) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            gameDraw = false;
        }
        return;
    }

    player.update(deltaTime);     

    if (!player.isDead && !player.isIdle) {
        scrollBackground();

        if (player.star.isShooting) player.star.update(deltaTime);
        enemy.update(deltaTime, player);
        jungleRunScoreText.setString(playerTurnScoreText[playerTurnIndex] + std::to_string(player.score));
    }

    if (player.isDead && player.isDeadAnimationOver) {
        runnerScore[playerTurnIndex] = player.score; // save player score

        if (playerTurnIndex == 1) { // both played a game
            if (runnerScore[RED_RUNNER] == runnerScore[BLUE_RUNNER])
                gameDraw = true;
            else // one is winner
                bothPlayed = true;
        }
        playerTurnIndex = 1 - playerTurnIndex; // if 0 changes to 1 and if 1 changes to 0
        resetJungleRun();
    }
}

void Jungle::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(bg1);
    window.draw(bg2);
    player.drawTo(window);
    player.star.drawTo(window);
    enemy.drawTo(window);
    window.draw(jungleRunScoreText);
    if (gameDraw)
        window.draw(gameStateRect[2]);
    else if (player.isIdle)
        window.draw(gameStateRect[playerTurnIndex]);
    window.display();
}

void Jungle::resetJungleRun() {
    enemy.resetEnemy();
    player.resetPlayer();
    jungleRunScoreText.setOutlineColor(playerColor[playerTurnIndex]);
    jungleRunScoreText.setString(playerTurnScoreText[playerTurnIndex] + "0");
}