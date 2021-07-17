#include "game.h"

Game::Game() {
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Duel: Multiplayer Battle", sf::Style::Titlebar | sf::Style::Close);
    // window.create(sf::VideoMode(), "Duel: Multiplayer Battle", sf::Style::Fullscreen);

    //Home page
    homeBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!homeTexture.loadFromFile("./images/home.jpg"))
        throw("ERR, Failed to load image file");  
    homeBackground.setTexture(&homeTexture);

    // Pong Bg
    pongBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!pongTexture.loadFromFile("./images/pingpong.jpg"))
        throw("ERR, Failed to load image file");  
    pongBackground.setTexture(&pongTexture);
    // Bat and Ball
    redBat.setBat(sf::Color::Red, 18);
    blueBat.setBat(sf::Color::Blue, WIDTH-18);

    // //Shooter Bg
    // shooterBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    // if (!shooterTexture.loadFromFile("./images/shooter.png"))
    //     throw("ERR, Failed to load image file");  
    // shooterBackground.setTexture(&shooterTexture);
    // // Shooter 
    // redShooter.setShooter("./images/red.png", 0, 1);
    // blueShooter.setShooter("./images/blue.png", WIDTH-75, -1);

    //Race Bg
    raceBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!raceTexture.loadFromFile("./images/space.jpg"))
        throw("ERR, Failed to load image file");  
    raceBackground.setTexture(&raceTexture);
    // Planes
    redPlane.setPlanePos(WIDTH/2-100);
    bluePlane.setPlanePos(WIDTH/2+100);
    // Boundry
    spaceRaceBoundry.setSize(sf::Vector2f(5, 250));
    spaceRaceBoundry.setPosition(WIDTH/2-5, HEIGHT-250);
    spaceRaceBoundry.setFillColor(sf::Color::White);

    // Sound
    setSound();

    // Text
    if (!font.loadFromFile("arial.ttf"))
        throw ("ERR, Failed to load font file");
    // home
    setText(title1, "DUEL BATTLE", 75, 100);
    // setTextOutline(title1, sf::Color::Black);
    setText(title2, "Pong, Space Race and Jungle Run", 25, 175);
    // game result page
    std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
    setText(scoreText, strMessage, 35, 15);
    // how To Play page
    setText(score3ToWinText, "Score 3 to Win!", 35, HEIGHT/2+50);
    setTextOutline(score3ToWinText, sf::Color::Magenta);
    setText(howToPlayText[1], "Use W, S to move Red Bat and Up, Down to move Blue bat", 35, HEIGHT/2);
    setText(howToPlayText[2], "Use W, S to move Red Plane and Up, Down to move Blue Plane", 35, HEIGHT/2);
    setText(howToPlayText[3], "Use Space to Jump Right to Shoot and Down to Slide", 35, HEIGHT/2);
    setText(gameNameText[1], "Ping Pong Battle", 50, 200);
    setText(gameNameText[2], "Space Race Battle", 50, 200);
    setText(gameNameText[3], "Jungle Run", 50, 200);

    for(int i=1; i<4; i++) {
        setTextOutline(gameNameText[i], sf::Color::Black);
        setTextOutline(howToPlayText[i], sf::Color::Magenta);
    }
    setText(startBattleText, "Start Battle!", 50, HEIGHT-200);
    // bottom text
    std::string nextGameString[5] = {"Press Space to play Ping Pong", "Space Race", "Jungle Run", "See the winner", "Press Enter to play again"};
    for (int i=0; i<5; i++) {
        setText(nextGameText[i], nextGameString[i], 35, HEIGHT-150);
        setTextOutline(nextGameText[i], sf::Color::Black);
    }
}


void Game::setText(sf::Text& text, std::string strMessage, int characterSize, int positionY) {
    text.setFont(font);
    text.setString(strMessage);
    text.setCharacterSize(characterSize); 
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(WIDTH/2, positionY);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Italic);
}

void Game::setTextOutline(sf::Text& text, sf::Color color) {
    text.setOutlineColor(color);
    text.setOutlineThickness(5);
}

void Game::setSound() {
    if (!buffer.loadFromFile("./sound/punch.wav"))
        throw("ERR, cant load sound");
    sound.setBuffer(buffer);
    // Background Music
    if (!music.openFromFile("./sound/aot.ogg"))
        throw("ERR, cant open music file");
    music.play();
    music.setVolume(30);
    music.setLoop(true);
}


void Game::run() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }            
        }

        switch(gameNumber) {
            case 0:
                homePage();
                break;
            case 1:
                if (showHowToPlay)
                    howToPlayPage(pongBackground);
                if (!showHowToPlay && !gameOver) 
                    pingPong();
                if (!showHowToPlay && gameOver) 
                    resultPage(pongBackground);
                break;
            case 2:
                if (showHowToPlay)
                    howToPlayPage(raceBackground);
                if (!showHowToPlay && !gameOver) 
                    spaceRace();
                if (!showHowToPlay && gameOver) 
                    resultPage(raceBackground);
                break;
            case 3:
                if (showHowToPlay)
                    howToPlayPage(shooterBackground);
                if (!showHowToPlay && !gameOver) 
                    shooterGame();
                if (!showHowToPlay && gameOver) 
                    resultPage(shooterBackground);
                break;
            case 4:
                endPage();
                break;
            default:
                break;
        }
    } // end of while window open
}


void  Game::homePage() {
    window.clear();
    window.draw(homeBackground);
    window.draw(title1);
    window.draw(title2);
    window.draw(nextGameText[0]);
    window.display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        gameNumber++;
}


void  Game::howToPlayPage(sf::RectangleShape& background) {
    window.clear();
    window.draw(background);
    window.draw(gameNameText[gameNumber]);
    window.draw(howToPlayText[gameNumber]);
    window.draw(score3ToWinText);
    window.draw(startBattleText);
    window.display();
    if (isMenuSelected(startBattleText))
        showHowToPlay = false;
}


void Game::endPage() {
    window.clear();
    window.draw(homeBackground);
    window.draw(scoreText);
    window.draw(winnerText);
    window.draw(nextGameText[4]);
    window.display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        resetGame();
    }
}


void Game::pingPong() {
    ball.moveBall();
    ball.checkBoundry(redBat, blueBat, sound);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        redBat.moveBat(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        redBat.moveBat(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        blueBat.moveBat(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        blueBat.moveBat(1);

    std::string strMessage = "Red: " + std::to_string(redBat.score) + "   Blue: " + std::to_string(blueBat.score); 
    scoreText.setString(strMessage);

    window.clear();
    window.draw(pongBackground);
    ball.drawTo(window);
    redBat.drawTo(window);
    blueBat.drawTo(window);
    window.draw(scoreText);
    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        blueBat.score = 3;
    checkGameOver(redBat.score, blueBat.score);
}

void Game::spaceRace() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        redPlane.move(-1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        redPlane.move(1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        bluePlane.move(-1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        bluePlane.move(1);

    redPlane.checkBoundry(WIDTH/2-100, sound); // starting X position is passed to reset 
    bluePlane.checkBoundry(WIDTH/2+100, sound);

    window.clear();
    window.draw(raceBackground);
    window.draw(spaceRaceBoundry);
    redPlane.drawTo(window);
    bluePlane.drawTo(window);
    //Asteroids
    for(int i=0; i<40; i++) {
        asteroid[i].move();
        asteroid[i].checkCollision(redPlane, bluePlane, sound);
        asteroid[i].drawTo(window);
    }
    std::string strMessage = "Red: " + std::to_string(redPlane.score) + "   Blue: " + std::to_string(bluePlane.score); 
    scoreText.setString(strMessage);
    window.draw(scoreText);
    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
        redPlane.score = 3;
    checkGameOver(redPlane.score, bluePlane.score);
}


void Game::shooterGame() {
    blueShooter.score = 3;
    checkGameOver(redShooter.score, blueShooter.score);
}


bool Game::isMenuSelected(sf::Text &text) {
    sf::Vector2i mouse;
    mouse = sf::Mouse::getPosition(window);
    if (text.getGlobalBounds().contains(mouse.x, mouse.y)) {
        text.setOutlineColor(sf::Color::Red);
        text.setOutlineThickness(3);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sound.play();
            return true;
        }
    } else {
        text.setOutlineThickness(0); 
    }
    return false;
}


void Game::resultPage(sf::RectangleShape &background) {
    if (isMenuSelected(nextGameText[gameNumber]))
        resetGame();
    window.clear();
    window.draw(background);
    window.draw(scoreText);
    window.draw(winnerText);
    window.draw(nextGameText[gameNumber]);
    window.display();
}


void Game::checkGameOver(int redScore, int blueScore)
{
    if (redScore == 3) {
        redFinalScore++;
        winner = "Red won!";
    }
    if (blueScore == 3) {
        blueFinalScore++;
        winner = "Blue won!";
    }
    if (winner != "None") {
        gameOver = true;
        setText(winnerText, winner, 70, 300);
        setTextOutline(winnerText, sf::Color::Black);
    }
}


void Game::resetGame() {
    gameOver = false;
    showHowToPlay = true;
    winner = "None";
    gameNumber++; // change game

    if (gameNumber == 4) {  // final result page
        if (redFinalScore > blueFinalScore) {
            winner = "Red won the series!";
        } else {
            winner = "Blue won the series!";
        }
        std::string strMessage = "Red: " + std::to_string(redFinalScore) + "   Blue: " + std::to_string(blueFinalScore); 
        scoreText.setString(strMessage);
        setText(winnerText, winner, 50, 100);
    }

    if (gameNumber==5) { // reset after end page
        gameNumber = 0;
        // reseting all scores
        redFinalScore = 0;
        blueFinalScore = 0;
        redBat.score = 0;
        blueBat.score = 0;
        redShooter.score = 0;
        blueShooter.score = 0;
        redPlane.score = 0;
        bluePlane.score = 0;
    }
}