#include "menu.h"

void gameMenu() {
    sf::RenderWindow window(sf::VideoMode(width, height), "2 Person Shooter");

    //Background Image of Window
    WindowBackground shooterBackground("./images/shooter.png"), shooterResult("./images/board.jpg");
    Shooter redShooter("./images/red.png", 0, 1), blueShooter("./images/blue.png", 750, -1);
    Bullet redBullet(sf::Color::Red), blueBullet(sf::Color::Blue);
    TextMessage scoreMessage;
    // Sound effects
    SoundManager gameSounds;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameOver) {
            redShooter.move();
            blueShooter.move();

            if (!redBullet.isFiring && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                redBullet.setPos(sf::Vector2f(redShooter.getX()+50, redShooter.getY()+25));
                redBullet.isFiring = true;
            }
            if (!blueBullet.isFiring && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                blueBullet.setPos(sf::Vector2f(blueShooter.getX()-50, blueShooter.getY()+25));
                blueBullet.isFiring = true;
            }

            window.clear();
            shooterBackground.drawTo(window);
            if (redBullet.isFiring) {
                redBullet.fire(1);
                redBullet.checkCollision(redShooter, blueShooter, gameSounds);
                redBullet.drawTo(window);
            }
            if (blueBullet.isFiring) {
                blueBullet.fire(-1);
                blueBullet.checkCollision(blueShooter, redShooter, gameSounds);
                blueBullet.drawTo(window);
            }

            std::string strMessage = "Red: " + std::to_string(redShooter.score) + "   Blue: " + std::to_string(blueShooter.score); 
            scoreMessage.changeString(strMessage);
            scoreMessage.drawTo(window);
            redShooter.drawTo(window);
            blueShooter.drawTo(window);
            window.display();
            checkGameOver(redShooter.score, blueShooter.score);
        }
    } // end of while window open
}