#include "run_player.h"
#include "global.h"

// float distanceTravelled = 0.f;

Player::Player() {
	if (!texture.loadFromFile("images/jungle/runner.png"))
		throw("ERR, couldn't load image");
    sprite.setTexture(texture);

    rowNo = 3;
    playerWidth = texture.getSize().x / 10;
    playerHeight = texture.getSize().y / 5;
    uvRect = sf::IntRect(0, rowNo * playerHeight, playerWidth, playerHeight);
    sprite.setTextureRect(uvRect);
    sprite.setScale(sf::Vector2f(0.4f, 0.4f));
    resetPosition();
}

void Player::resetPosition() {
    sprite.setPosition(25, HEIGHT -  sprite.getGlobalBounds().height - 50);
}

void Player::update(float deltaTime) {
    this->deltaTime = deltaTime;
    totalTime += deltaTime;

    // Start running
    if (isIdle && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        isIdle = false;
        totalTime = 0;
        rowNo = 3;
        imageNo = 0;
    }

    // start jumping
    if (!isJumping && !isSliding && !isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        isJumping = true;
        totalTime = 0;
        imageNo = 0;
        rowNo = 2;
    }

    // start sliding
    if (!isSliding && !isJumping && !isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        isSliding = true;
        totalTime = 0;
        imageNo = 0;
        rowNo = 4;
        // sprite.setScale(0.3, 0.3);
        sprite.move(0, 35);
    }

    // start shooting
    if (!star.isShooting && !isDead && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        star.isShooting = true;
        star.setPos(sf::Vector2f(sprite.getPosition().x+0.4*playerWidth, sprite.getPosition().y+50));
    }

    if (isDead)
        dead();
    else if (isJumping)
        jump();
    else if (isSliding)
        slide();
    else if (isIdle) {
        idle();
    } else {
        run();
    }
}


void Player::idle() {
    rowNo = 0;
    if (totalTime >= switchTime.idle) {
        totalTime -= switchTime.idle;
        imageNo++;
        if (imageNo > 9)
            imageNo = 0;
        uvRect.left = imageNo * playerWidth;
        uvRect.top = 0;
        sprite.setTextureRect(uvRect);
    }
}

void Player::run() {
    rowNo = 3;
    if (totalTime >= switchTime.run) {
        totalTime -= switchTime.run;
        imageNo++;
        if (imageNo > 9)
            imageNo = 0;
        uvRect.left = imageNo * playerWidth;
        uvRect.top = rowNo * playerHeight;
        sprite.setTextureRect(uvRect);
    }
}


void Player::jump() {
    if (totalTime >= switchTime.jump) {
        totalTime -= switchTime.jump;
        imageNo++;
        if (imageNo > 9) {
            resetPosition();
            isJumping = false;
        }
        uvRect.left = imageNo * playerWidth;
        uvRect.top = rowNo * playerHeight;
        sprite.setTextureRect(uvRect);
    }
    sprite.move(0, (imageNo - 5) * 0.3f);
    // // checking only
    // float heightJumped = HEIGHT - sprite.getPosition().y;
    // if (imageNo == 5) std::cout << "HT Y = " << heightJumped << '\t'; 
    // // // ans = 400
    // distanceTravelled += -SCROLL_SPEED;
    // if (imageNo == 9 && distanceTravelled > 50) {
    //     std::cout << "Dist X = " << distanceTravelled << '\t';
    //     distanceTravelled = 0;
    // }
    // // ans = 320 to 350
}

void Player::slide() {
    if (totalTime >= switchTime.slide) {
        totalTime -= switchTime.slide;
        imageNo++;
        if (imageNo > 9) {
            resetPosition();
            isSliding = false;
        }
        uvRect.left = imageNo * playerWidth;
        uvRect.top = rowNo * playerHeight;
        sprite.setTextureRect(uvRect);
    }
}


void Player::dead() {
    if (totalTime >= switchTime.dead) {
        totalTime -= switchTime.dead;
        imageNo++;
        if (imageNo > 9) {
            imageNo = 9;
            isDeadAnimationOver = true;
        }
        uvRect.left = imageNo * playerWidth;
        uvRect.top = rowNo * playerHeight;
        sprite.setTextureRect(uvRect);
    }
}

void Player::kill()
{
    // change variables to allow dead animation 
    // (this is to be done only once) as this function is called everytime after death
    if (!isDead) {
        isJumping = false;
        totalTime = 0;
        rowNo = 1;
        imageNo = 0;
        resetPosition();
    } 
    // dead status so above if block doesn't run next time 
    // also dead animation runs now in player->update
    isDead = true;

}

sf::FloatRect Player::globalBounds()
{
    sf::FloatRect globalRect = sprite.getGlobalBounds();
    globalRect.width -= 25.f; // to make easier
    globalRect.height -= 10.f;
    return globalRect;
}

void Player::resetPlayer() {
    isDead = false;
    isDeadAnimationOver = false;
    isIdle = true;
    resetPosition();
    star.setPos(sf::Vector2f(0, 0));
    star.isShooting = false;
    score = 0;
}


Star::Star() {
    this->speed = 0.9f;
    this->switchTime = 0.1f;

	if (!texture.loadFromFile("images/jungle/stars.png"))
		throw("err, cant load image");
	sprite.setTexture(texture);
	sprite.setScale(0.2f, 0.2f);
	this->objectWidth = texture.getSize().x/2; 
	uvRect = sf::IntRect(0, 0, objectWidth, texture.getSize().y);
	sprite.setTextureRect(uvRect);
}

void Star::setPos(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Star::update(float deltaTime) {
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		imageNo++;
		if (imageNo > 1)
			imageNo = 0;
		uvRect.left = imageNo * objectWidth;
		sprite.setTextureRect(uvRect);
	}

	sprite.move(speed, 0);
	if (sprite.getPosition().x > WIDTH) {
		sprite.setPosition(0, 0);
        isShooting = false;
	}
}

sf::FloatRect Star::globalBounds()
{
    return sprite.getGlobalBounds();
}