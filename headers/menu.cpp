#include "menu.h"

Game::Game() {
    window.create(sf::VideoMode(1366, 768), "2 Person Shooter");
    width = window.getSize().x;
    height = window.getSize().y;
    // std::cout << width << "," << height;
    // (width, height) = (1366, 768)

    //Shooter Bg
    shooterBackground.setSize(sf::Vector2f(width, height));
    if (!shooterTexture.loadFromFile("./images/shooter.png"))
        throw("ERR, Failed to load image file");  
    shooterBackground.setTexture(&shooterTexture);
    // Shooter 
    redShooter.setShooter("./images/red.png", 0, 1);
    blueShooter.setShooter("./images/blue.png", width-75, -1);
    redBullet.setBullet();
    blueBullet.setBullet();

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
    // Asteroids


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
    std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
    setText(scoreMessage, strMessage, 25, 15);
    setText(playAgainInstructions, "Space Racer!", 25, height-200);


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
    // music.play();
    music.setVolume(50);
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
        }

        switch(gameNumber) {
            case 0:
                if (!gameOver) 
                    shooterGame();
                if (gameOver) 
                    resultPage();
                break;
            case 1:
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

void Game::shooterGame() {
    redShooter.move();
    blueShooter.move();
    redShooter.checkBoundry(height);
    blueShooter.checkBoundry(height);

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
        redBullet.checkCollision(redShooter, blueShooter, sound, width);
        redBullet.drawTo(window);
    }
    if (blueBullet.isFiring) {
        blueBullet.fire(-2);
        blueBullet.checkCollision(blueShooter, redShooter, sound, width);
        blueBullet.drawTo(window);
    }

    std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
    scoreMessage.setString(strMessage);
    window.draw(scoreMessage);

    redShooter.drawTo(window);
    blueShooter.drawTo(window);
    window.display();
    checkGameOver(redShooter.score, blueShooter.score);
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

    // Check Collision
    //redPlane.checkCollision();
    // bluePlane.checkCollision();

    window.clear();
    window.draw(raceBackground);
    window.draw(spaceRaceBoundry);
    std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
    scoreMessage.setString(strMessage);
    redPlane.drawTo(window);
    bluePlane.drawTo(window);
    //Asteroids
    for(int i=0; i<30; i++) {
        asteroid[i].move();
        asteroid[i].drawTo(window);
    }
    window.draw(scoreMessage);
    window.display();
    checkGameOver(redPlane.score, bluePlane.score);
}

void Game::resultPage() {
    sf::Vector2i mouse;
    mouse = sf::Mouse::getPosition(window);
    if (playAgainInstructions.getGlobalBounds().contains(mouse.x, mouse.y)) {
        playAgainInstructions.setOutlineColor(sf::Color::Red);
        playAgainInstructions.setOutlineThickness(3);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            resetGame();
        }
    } else {
        playAgainInstructions.setOutlineThickness(0); 
    }

    window.clear();
    window.draw(resultBackground);
    window.draw(winnerMessage);
    window.draw(playAgainInstructions);
    window.display();
}

void Game::checkGameOver(int redScore, int blueScore)
{
    if (redScore == 3)
        winner = "Red won!";
    if (blueScore == 3)
        winner = "Blue won!";
    if (winner != "None")
        gameOver = true;
    setText(winnerMessage, winner, 50, height/2);
}

void Game::resetGame() {
    gameOver = false;
    redShooter.score = 0;
    blueShooter.score = 0;
    winner = "None";
    sound.play();
    gameNumber++; // change game
}