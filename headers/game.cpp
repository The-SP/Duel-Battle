#include "game.h"

Game::Game() {
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Duel: Multiplayer Battle", sf::Style::Titlebar | sf::Style::Close);

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
    initText(title1, "DUEL Game Package", 75, 100);
    initText(title2, "Pong, Space Race and Jungle Run", 25, 175);
    // game result page
    std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
    initText(scoreText, strMessage, 35, 15);

    // How To Play
    initTexture(howToRect[1], howToTexture[1], sf::Vector2f(700, 400), "images/pongHowTo.jpg");
    initTexture(howToRect[2], howToTexture[2], sf::Vector2f(700, 400), "images/spaceHowTo.jpg");
    initTexture(howToRect[3], howToTexture[3], sf::Vector2f(700, 400), "images/jungleHowTo.jpg");
    for (int i=1; i<4; i++) {
        howToRect[i].setOutlineColor(sf::Color::White);
        howToRect[i].setOutlineThickness(3.f);
    }

    // Buttons 
    initTexture(playButton, buttonTexture[0], sf::Vector2f(100, 100), "images/redButton.png");
    if (!buttonTexture[1].loadFromFile("images/greenButton.png"))
        throw("ERR, Failed to load image file");  
    playButton.setPosition(WIDTH/2-playButton.getSize().x/2, HEIGHT-150);
}

void Game::initTexture(sf::RectangleShape& rect, sf::Texture& texture, const sf::Vector2f& size, const std::string& imageFile) {
    rect.setSize(size);
    if (!texture.loadFromFile(imageFile))
        throw("ERR, Failed to load image file");  
    rect.setTexture(&texture);
    rect.setPosition(WIDTH/2-rect.getSize().x/2, HEIGHT/2-rect.getSize().y/2);   
}


void Game::initText(sf::Text& text, std::string strMessage, int characterSize, int positionY) {
    text.setFont(font);
    text.setString(strMessage);
    text.setCharacterSize(characterSize); 
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(WIDTH/2, positionY);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Italic);
}

void Game::setSound() {
    if (!buffer.loadFromFile("./sound/punch.wav"))
        throw("ERR, cant load sound");
    sound.setBuffer(buffer);
    // Background Music
    if (!music.openFromFile("./sound/aot.ogg"))
        throw("ERR, cant open music file");
    music.play();
    music.setVolume(10);
    music.setLoop(true);
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
                    jungleRun();
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


void Game::endPage() {
    window.clear();
    window.draw(homeBackground);
    window.draw(scoreText);
    window.draw(winnerText);
    window.draw(playButton);
    window.display();
    if (isButtonSelected(playButton)) {
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


void Game::jungleRun() {
    blueShooter.score = 3;
    checkGameOver(redShooter.score, blueShooter.score);
}


bool Game::isButtonSelected(sf::RectangleShape &button) {
    sf::Vector2i mouse;
    mouse = sf::Mouse::getPosition(window);
    if (button.getGlobalBounds().contains(mouse.x, mouse.y)) {
        button.setTexture(&buttonTexture[1]);
        if (buttonPressedEvent && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sound.play();
            buttonPressedEvent = false;
            return true;
        }
    } else {
        button.setTexture(&buttonTexture[0]);
        button.setOutlineThickness(0);
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


void Game::checkGameOver(int redScore, int blueScore)
{
    if (redScore == 3) {
        redFinalScore++;
        winner = "Red won!";
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
        winnerText.setOutlineThickness(5.f);
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
        initText(winnerText, winner, 50, 100);
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