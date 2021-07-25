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

    if (!gameStateTexture[0].loadFromFile("images/jungle/red_turn.jpg") || !gameStateTexture[1].loadFromFile("images/jungle/blue_turn.jpg") || !gameStateTexture[2].loadFromFile("images/jungle/score_draw.jpg"))
        throw("ERR, Failed to load image");
    for (int i=0; i<3; i++) {
        gameStateRect[i].setSize(sf::Vector2f(700, 400));
        gameStateRect[i].setTexture(&gameStateTexture[i]);
        gameStateRect[i].setPosition(WIDTH/2-gameStateRect[i].getSize().x/2, HEIGHT/2-150);
        gameStateRect[i].setOutlineColor(sf::Color::White);
        gameStateRect[i].setOutlineThickness(3.f);
    }

    // Init Text
    if (!font.loadFromFile("fonts/pixel.ttf"))
        throw("Err, can't load font filel");
    TextMessage::initText(font, jungleRunScoreText, "Red Score: 0", 50, 0);
	jungleRunScoreText.setPosition(WIDTH-150, 0);
    jungleRunScoreText.setOutlineThickness(1);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
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
    jungleRunScoreText.setString(playerTurnScoreText[playerTurnIndex] + std::to_string(player.score));
    // jungleRunScoreText.setString(playerTurnScoreText[playerTurnIndex] + std::to_string(0));
}
   
