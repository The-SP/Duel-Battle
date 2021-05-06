#include "ball.h"

Ball::Ball() {
    ball.setRadius(radius);
    ball.setFillColor(sf::Color{255, 165, 0});
    ball.setOrigin(10, 10);
    ball.setPosition(width/2, height/2);  //position of origin of ball(i.e centre of ball in this case)
}

void Ball::moveBall() {
    ball.move(speedX, speedY);
}

void Ball::resetPosition() {
    ball.setPosition(width/2, height/2);
}

void Ball::checkBoundry(Bat& red, Bat& blue, sf::Sound &sound) {
    if (ball.getPosition().x > width - 10)
    { // here -10 is done becz origin of ball at (10, 10)
        resetPosition();
        red.score++;
        speedX *= -1;
        // to create slightly random y motion after restart
        speedY *= -1;
        sound.play();

    }
    if (ball.getPosition().x < 10)
    {
        resetPosition();
        blue.score++;
        speedX *= -1;
        sound.play();

    }
    // Vertical boundry
    if (ball.getPosition().y > height - 10 || ball.getPosition().y < 10)
    {
        speedY *= -1;
        sound.play();
    }

    // CHECK COLLISION WITH BAT
    /* Note: 
    here ball.setPosition(50, ballPos.y) done becz 
    if collide and speedX*=-1 done then still the condition is satisfied immediately and 
    it gives continuous loop (ball slides along the bat or ball freezes) (weird error for some cases)
    so we set the ball position clearly away from bat by 50 or width-50 this removes such error by 
    avoiding immediate collision condition after direction change
    */
    if (ball.getGlobalBounds().intersects(red.globalBounds())) { 
        ball.setPosition(50, ball.getPosition().y);
        speedX *= -1;
        sound.play();
    }
    if (ball.getGlobalBounds().intersects(blue.globalBounds())) {
        ball.setPosition(width-50, ball.getPosition().y);
        speedX *= -1;
        sound.play();
    }
}

void Ball::drawTo(sf::RenderWindow &window) {
    window.draw(ball);
}