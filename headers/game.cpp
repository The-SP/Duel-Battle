#include "game.h"

Game::Game() {
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Duel: Multiplayer Battle", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i(0, 0));
    window.setFramerateLimit(60);

    //Home page
    homeBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!homeTexture.loadFromFile("./images/home.jpg"))
        throw("ERR, Failed to load image file");  
    homeBackground.setTexture(&homeTexture);

    // Result
    resultBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!resutlTexture.loadFromFile("./images/result.jpg"))
        throw("ERR, Failed to load image file");  
    resultBackground.setTexture(&resutlTexture);

    // Ping Pong Bg
    pongBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!pongTexture.loadFromFile("./images/pingpong.jpg"))
        throw("ERR, Failed to load image file");  
    pongBackground.setTexture(&pongTexture);
    // Bat and Ball
    redBat.setBat(sf::Color::Red, 18);
    blueBat.setBat(sf::Color::Blue, WIDTH-18);

    // Space Race Bg
    spaceBackground[0].setSize(sf::Vector2f(WIDTH, HEIGHT));
    spaceBackground[1].setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!spaceTexture[0].loadFromFile("./images/space.jpg") || !spaceTexture[1].loadFromFile("./images/space1.jpg"))
        throw("ERR, Failed to load image file");   
    spaceBackground[0].setTexture(&spaceTexture[0]);
    spaceBackground[1].setTexture(&spaceTexture[1]);
    // Asteroid texture
    if (!asteroidTexture[0].loadFromFile("images/asteroid1.png") || !asteroidTexture[1].loadFromFile("images/asteroid2.png") || !asteroidTexture[2].loadFromFile("images/asteroid3.png"))
        throw("ERR, Failed to load image file");  
    for (int i=0; i<asteroidSize; i++)
        asteroid[i].initTexture(asteroidTexture[rand()%3]);
    // Planes
    redPlane.resetPlane(WIDTH/2-100);
    bluePlane.resetPlane(WIDTH/2+100);
    // Boundry
    spaceRaceBoundry.setSize(sf::Vector2f(4, 250));
    spaceRaceBoundry.setPosition(WIDTH/2-2, HEIGHT-250);
    spaceRaceBoundry.setFillColor(sf::Color::White);

    // Jungle Run
    jungleBackground.setSize(sf::Vector2f(WIDTH, HEIGHT));
    if (!jungleTexture.loadFromFile("./images/jungle/bg111.png"))
        throw("ERR, Failed to load image file");  
    jungleBackground.setTexture(&jungleTexture);

    // Sound
    initSound();
    // Text
    if (!font.loadFromFile("fonts/arial.ttf") || !scoreFont.loadFromFile("fonts/Hermes-Regular.ttf"))
        throw ("ERR, Failed to load font file");
    // home
    initText(title1, "DUEL Game Package", 75, 100);
    title1.setOutlineThickness(4.f);
    initText(title2, "Ping Pong, Space Race and Jungle Run", 25, 175);
    // score and winner
    initText(scoreText, "Red: 0   Blue: 0", 40, 15);
    scoreText.setFont(scoreFont);
    scoreText.setStyle(sf::Text::Regular);
    winnerText.setOutlineThickness(5.f);

    // How To Play Card
    initTexture(howToRect[1], howToTexture[1], sf::Vector2f(700, 400), "images/pongHowTo.jpg");
    initTexture(howToRect[2], howToTexture[2], sf::Vector2f(700, 400), "images/spaceHowTo.jpg");
    initTexture(howToRect[3], howToTexture[3], sf::Vector2f(700, 400), "images/jungleHowTo.jpg");

    // Buttons 
    initTexture(playButton, buttonTexture[0], sf::Vector2f(100, 100), "images/redButton.png");
    if (!buttonTexture[1].loadFromFile("images/greenButton.png"))
        throw("ERR, Failed to load image file");  
    playButton.setPosition(WIDTH/2-playButton.getSize().x/2, HEIGHT-150);
}

void Game::initSound() {
    if (
        !buffer.loadFromFile("./sound/punch.wav") ||
        !pongBuffer.loadFromFile("./sound/pong.wav") ||
        !raceBuffer.loadFromFile("sound/race.ogg") ||
        !cheerBuffer.loadFromFile("./sound/Cheer.wav")
      )
        throw("ERR, cant load sound");
    sound.setBuffer(buffer);
    pongSound.setBuffer(pongBuffer);
    raceSound.setBuffer(raceBuffer);
    cheerSound.setBuffer(cheerBuffer);
    // Background Music
    if (!music.openFromFile("./sound/aot.ogg"))
        throw("ERR, cant open music file");
    music.play();
    music.setVolume(25);
    music.setLoop(true);
    sound.setVolume(25);
    cheerSound.setVolume(35);
}


void Game::run() {
    sf::Clock clock;
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
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
            if (event.type == sf::Event::MouseButtonPressed)
                buttonPressedEvent = true;
        }

        switch(gameNumber) {
            case HOME_INDEX:
                homePage();
                break;
            case PING_PONG:
                if (showHowToPlay)
                    howToPlayPage(pongBackground);
                if (!showHowToPlay && !gameOver) 
                    pingPong();
                if (!showHowToPlay && gameOver) 
                    resultPage(pongBackground);
                break;
            case SPACE_RACE:
                if (showHowToPlay)
                    howToPlayPage(spaceBackground[0]);
                if (!showHowToPlay && !gameOver) 
                    spaceRace();
                if (!showHowToPlay && gameOver) 
                    resultPage(spaceBackground[0]);
                break;
            case JUNGLE_RUN:
                if (showHowToPlay)
                    howToPlayPage(jungleBackground);
                if (!showHowToPlay && !gameOver) 
                    jungleRun();
                if (!showHowToPlay && gameOver) 
                    resultPage(jungleBackground);
                break;
            case RESULT_INDEX:
                endPage();
                break;
            default:
                break;
        }
    } // end of while window open
}


void  Game::homePage() {
    textBlink(title1, deltaTime);
    window.clear();
    window.draw(homeBackground);
    window.draw(title1);
    window.draw(title2);
    window.draw(playButton);
    window.display();
    if (isButtonSelected(playButton))
        gameNumber++;
}


void Game::howToPlayPage(sf::RectangleShape& background) {
    window.clear();
    window.draw(background);
    window.draw(playButton);
    window.draw(howToRect[gameNumber]);
    window.display();
    if (isButtonSelected(playButton))
        showHowToPlay = false;
}


void Game::pingPong() {
    if (ball.isMoving) {
        ball.moveBall();
        ball.checkBoundry(redBat, blueBat, pongSound);
    } else { // ball is paused for little time before serve
        ball.pauseBall(deltaTime);
    }

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace)) // Game Skip option
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

    redPlane.checkBoundry(WIDTH/2-100, raceSound); // starting X position is passed to reset 
    bluePlane.checkBoundry(WIDTH/2+100, raceSound);

    std::string strMessage = "Red: " + std::to_string(redPlane.score) + "   Blue: " + std::to_string(bluePlane.score); 
    scoreText.setString(strMessage);

    window.clear();
    window.draw(spaceBackground[Plane::currentSpaceBackgroundIndex]);
    window.draw(spaceRaceBoundry);
    redPlane.drawTo(window);
    bluePlane.drawTo(window);
    //Asteroids
    for(int i=0; i<asteroidSize; i++) {
        asteroid[i].move();
        asteroid[i].checkCollision(redPlane, bluePlane, sound);
        asteroid[i].drawTo(window);
    }
    window.draw(scoreText);
    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace)) // Game Skip option
        redPlane.score = 3;
    checkGameOver(redPlane.score, bluePlane.score);
}


void Game::jungleRun() {
    jungle.update(deltaTime);
    jungle.render(window);
    if (jungle.bothPlayed) {
        gameOver = true;
        jungle.bothPlayed = false;
        if (jungle.runnerScore[0] > jungle.runnerScore[1]) 
            checkGameOver('r'); // red won
        else if (jungle.runnerScore[0] < jungle.runnerScore[1])
            checkGameOver('b'); // blue won
        std::string strMessage = "Red: " + std::to_string(jungle.runnerScore[0]) + "   Blue: " + std::to_string(jungle.runnerScore[1]); 
        scoreText.setString(strMessage);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace)) { // game skip functionality
        checkGameOver('b'); // making blue winner
        jungle.playerTurnIndex = 0; // red turn
        jungle.resetJungleRun();
    }
}

void Game::textBlink(sf::Text& text, float deltaTime, float switchTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		text.setOutlineColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
	}
}


bool Game::isButtonSelected(sf::RectangleShape &button) {
    sf::Vector2i mouse;
    mouse = sf::Mouse::getPosition(window);
    if (button.getGlobalBounds().contains(mouse.x, mouse.y)) {
        button.setTexture(&buttonTexture[1]);
        button.setScale(1.05, 1.05);
        if (buttonPressedEvent && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sound.play();
            buttonPressedEvent = false;
            return true;
        }
    } else {
        button.setTexture(&buttonTexture[0]);
        button.setScale(1, 1);
    }
    return false;
}


void Game::resultPage(sf::RectangleShape &background) {
    if (isButtonSelected(playButton))
        resetGame();
    window.clear();
    window.draw(background);
    window.draw(scoreText);
    window.draw(winnerText);
    window.draw(playButton);
    window.display();
}

void Game::endPage() {
    if (isButtonSelected(playButton))
        resetGame();
    window.clear();
    window.draw(resultBackground);
    window.draw(scoreText);
    window.draw(winnerText);
    window.draw(playButton);
    window.display();
}


void Game::checkGameOver(int redScore, int blueScore)
{
    if (redScore == 3) {
        redFinalScore++;
        winner = "Red  won!";
        winnerText.setOutlineColor(sf::Color::Red);
    }
    if (blueScore == 3) {
        blueFinalScore++;
        winner = "Blue won!";
        winnerText.setOutlineColor(sf::Color::Blue);
    }
    if (winner != "None") {
        gameOver = true;
        initText(winnerText, winner, 70, 300);
    }
}

void Game::checkGameOver(char winnerColor)
{
    if (winnerColor == 'r') {
        redFinalScore++;
        winner = "Red  won!";
        winnerText.setOutlineColor(sf::Color::Red);
    }else {
        blueFinalScore++;
        winner = "Blue won!";
        winnerText.setOutlineColor(sf::Color::Blue);
    }
    gameOver = true;
    initText(winnerText, winner, 70, 300);
}


void Game::resetGame() {
    gameOver = false;
    showHowToPlay = true;
    winner = "None";
    gameNumber++; // change game

    if (gameNumber == RESULT_INDEX) {  // final result page => 4
        if (redFinalScore > blueFinalScore) {
            winner = "Red won the series!";
            winnerText.setOutlineColor(sf::Color::Red);       
        } else {
            winner = "Blue won the series!";
            winnerText.setOutlineColor(sf::Color::Blue);
        }
        std::string strMessage = "Red: " + std::to_string(redFinalScore) + "   Blue: " + std::to_string(blueFinalScore); 
        scoreText.setString(strMessage);
        initText(winnerText, winner, 50, 100);
        cheerSound.play();
    }

    if (gameNumber == RESULT_INDEX + 1) { // reset after end page => 5
        gameNumber = HOME_INDEX; //0
        // reseting all scores
        redFinalScore = 0;
        blueFinalScore = 0;
        redBat.score = 0;
        blueBat.score = 0;
        // reset Jungle runner score = 0
        redPlane.score = 0;
        bluePlane.score = 0;

        // reset game objects position
        ball.resetPosition();
        redPlane.resetPlane(WIDTH/2-100);
        bluePlane.resetPlane(WIDTH/2+100);
    }
}