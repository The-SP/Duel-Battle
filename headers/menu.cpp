#include "menu.h"

Game::Game() {
    /* 
        Note: 
        while using sf::Style::Fullscreen it lags sometimes 
        so use (1366, 768) but while using this the window does not exactly start from top left 
        as it includes taskbar and some other weird reasons
        so  find best way for fullscreen
    */
    window.create(sf::VideoMode(), "Duel: Multiplayer Battle", sf::Style::Fullscreen);
    // window.create(sf::VideoMode(1366, 768), "Duel: Multiplayer Battle");
    width = window.getSize().x;
    height = window.getSize().y;
    // std::cout << width << "," << height;
    // (width, height) = (1366, 768)

    //Home page
    homeBackground.setSize(sf::Vector2f(width, height));
    if (!homeTexture.loadFromFile("./images/home.jpg"))
        throw("ERR, Failed to load image file");  
    homeBackground.setTexture(&homeTexture);

    // Pong Bg
    pongBackground.setSize(sf::Vector2f(width, height));
    if (!pongTexture.loadFromFile("./images/pingpong.jpg"))
        throw("ERR, Failed to load image file");  
    pongBackground.setTexture(&pongTexture);
    // Bat and Ball
    redBat.setBat(sf::Color::Red, 18);
    blueBat.setBat(sf::Color::Blue, width-18);

    //Shooter Bg
    shooterBackground.setSize(sf::Vector2f(width, height));
    if (!shooterTexture.loadFromFile("./images/shooter.png"))
        throw("ERR, Failed to load image file");  
    shooterBackground.setTexture(&shooterTexture);
    // Shooter 
    redShooter.setShooter("./images/red.png", 0, 1);
    blueShooter.setShooter("./images/blue.png", width-75, -1);

    //Race Bg
    raceBackground.setSize(sf::Vector2f(width, height));
    if (!raceTexture.loadFromFile("./images/space.jpg"))
        throw("ERR, Failed to load image file");  
    raceBackground.setTexture(&raceTexture);
    // Planes
    redPlane.setPlanePos(width/2-100);
    bluePlane.setPlanePos(width/2+100);
    // Boundry
    spaceRaceBoundry.setSize(sf::Vector2f(5, 250));
    spaceRaceBoundry.setPosition(width/2-5, height-250);
    spaceRaceBoundry.setFillColor(sf::Color::White);

    //Result Bg
    resultBackground.setSize(sf::Vector2f(width, height));
    if (!resultTexture.loadFromFile("./images/board.jpg"))
        throw("ERR, Failed to load image file");  
    resultBackground.setTexture(&resultTexture); 

    // Sound
    setSound();

    // Text
    if (!font.loadFromFile("arial.ttf"))
        throw ("ERR, Failed to load font file");
    setText(title, "DUEL", 50, 100);
    setText(howToPlay, "Use Up, Down to move Blue and W, S to move Red!", 25, height-200);
    std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
    setText(scoreMessage, strMessage, 25, 15);
    setText(playInstructions, "Ping Pong Game", 25, height-100);
}


void Game::setText(sf::Text& text, std::string strMessage, int characterSize, int positionY) {
    text.setFont(font);
    text.setString(strMessage);
    text.setCharacterSize(characterSize); 
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(width/2, positionY);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Italic);
}


void Game::setSound() {
    // load Punch Sound to buffer
    if (!buffer.loadFromFile("./sound/punch.wav"))
        throw("ERR, cant load sound");
    sound.setBuffer(buffer);
    // Background Music
    if (!music.openFromFile("./sound/aot.ogg"))
        throw("ERR, cant open music file");
    music.play();
    music.setVolume(20);
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
                if (!gameOver) 
                    pingPong();
                if (gameOver) 
                    resultPage();
                break;
            case 2:
                if (!gameOver) 
                    shooterGame();
                if (gameOver) 
                    resultPage();
                break;
            case 3:
                if (!gameOver) 
                    spaceRace();
                if (gameOver) 
                    resultPage();
                break;
            default:
                break;
        }
    } // end of while window open
}


void  Game::homePage() {
    selectMenuOption();
    window.clear();
    window.draw(homeBackground);
    window.draw(title);
    window.draw(howToPlay);
    window.draw(playInstructions);
    window.display();
}

void Game::pingPong() {
    // Move ball
    ball.moveBall();
    // Check ball boundry conditions and collision with bat
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
    scoreMessage.setString(strMessage);

    window.clear();
    window.draw(pongBackground);
    ball.drawTo(window);
    redBat.drawTo(window);
    blueBat.drawTo(window);
    window.draw(scoreMessage);
    window.display();
    checkGameOver(redBat.score, blueBat.score);
    // setting up result page instruction
    setText(playInstructions, "Shooter Game", 25, height-100);
}


void Game::shooterGame() {
    redShooter.move();
    blueShooter.move();
    redShooter.checkBoundry();
    blueShooter.checkBoundry();

    if (!redBullet.isFiring && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        redBullet.setPos(sf::Vector2f(redShooter.getX()+50, redShooter.getY()+75/2));
        redBullet.isFiring = true;
    }
    if (!blueBullet.isFiring && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
        blueBullet.setPos(sf::Vector2f(blueShooter.getX()-50, blueShooter.getY()+75/2));
        blueBullet.isFiring = true;
    }

    window.clear();
    window.draw(shooterBackground);
    if (redBullet.isFiring) {
        redBullet.fire(2);
        redBullet.checkCollision(redShooter, blueShooter, sound);
        redBullet.drawTo(window);
    }
    if (blueBullet.isFiring) {
        blueBullet.fire(-2);
        blueBullet.checkCollision(blueShooter, redShooter, sound);
        blueBullet.drawTo(window);
    }

    std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
    scoreMessage.setString(strMessage);
    window.draw(scoreMessage);

    redShooter.drawTo(window);
    blueShooter.drawTo(window);
    window.display();
    checkGameOver(redShooter.score, blueShooter.score);
    // setting up result page instruction
    setText(playInstructions, "Space Race", 25, height-100);
}

void Game::spaceRace() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        redPlane.move(-1);
        redPlane.checkBoundry(width/2-100, sound); // starting X position is passed to reset 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        redPlane.move(1);
        redPlane.checkBoundry(width/2-100, sound); // starting X position is passed to reset 
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        bluePlane.move(-1);
        bluePlane.checkBoundry(width/2+100, sound);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        bluePlane.move(1);
        bluePlane.checkBoundry(width/2+100, sound);
    }

    window.clear();
    window.draw(raceBackground);
    window.draw(spaceRaceBoundry);
    std::string strMessage = "Red: " + std::to_string(redPlane.score) + "   Blue: " + std::to_string(bluePlane.score); 
    scoreMessage.setString(strMessage);
    redPlane.drawTo(window);
    bluePlane.drawTo(window);
    //Asteroids
    for(int i=0; i<30; i++) {
        asteroid[i].move();
        asteroid[i].checkCollision(redPlane, bluePlane, sound);
        asteroid[i].drawTo(window);
    }
    window.draw(scoreMessage);
    window.display();
    checkGameOver(redPlane.score, bluePlane.score);
    // setting up result page instruction
    setText(playInstructions, "Main Menu", 25, height-100);
}


void Game::selectMenuOption() {
    sf::Vector2i mouse;
    mouse = sf::Mouse::getPosition(window);
    if (playInstructions.getGlobalBounds().contains(mouse.x, mouse.y)) {
        playInstructions.setOutlineColor(sf::Color::Red);
        playInstructions.setOutlineThickness(3);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            resetGame();
        }
    } else {
        playInstructions.setOutlineThickness(0); 
    }
}


void Game::resultPage() {
    selectMenuOption();
    window.clear();
    window.draw(resultBackground);
    window.draw(winnerMessage);
    window.draw(playInstructions);
    window.display();
}


void Game::checkGameOver(int redScore, int blueScore)
{
    if (redScore == 1)
        winner = "Red won!";
    if (blueScore == 3)
        winner = "Blue won!";
    if (winner != "None") {
        gameOver = true;
    }
    setText(winnerMessage, winner, 50, height/2);
}


void Game::resetGame() {
    gameOver = false;
    redBat.score = 0;
    blueBat.score = 0;
    redShooter.score = 0;
    blueShooter.score = 0;
    redPlane.score = 0;
    bluePlane.score = 0;
    winner = "None";
    sound.play();
    gameNumber++; // change game
    if (gameNumber==4) 
        gameNumber = 0;
}