#include "run_enemy.h"
#include "global.h"

Bird::Bird()
{
	this->speed = 2.5f*SCROLL_SPEED;
	this->switchTime = 0.2f;

	if (!texture.loadFromFile("images/jungle/birds.png"))
		throw("err, cant load image");
	sprite.setTexture(texture);

	sprite.setScale(0.15f, 0.15f);
	this->objectWidth = texture.getSize().x/2; 
	this->objectHeight = texture.getSize().y/2;
	uvRect = sf::IntRect(0, 0, objectWidth, objectHeight);
	sprite.setTextureRect(uvRect);
	sprite.setPosition(WIDTH*2, HEIGHT-200);

    if (!starHitBuffer.loadFromFile("sound/star_throw.wav"))
        throw("ERR, can't load music");
    starHitSound.setBuffer(starHitBuffer);
}

void Bird::update(Player& player, float deltaTime) {
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		imageNo++;
		if (imageNo > 1)
			imageNo = 0;
		uvRect.left = imageNo * objectWidth;
		uvRect.top = rowNo * objectHeight;
		sprite.setTextureRect(uvRect);
	}
	
	sprite.move(speed, speedY);
	// bird out of screen
	if (sprite.getPosition().x < -50) {
		if (speedY != 0) { // reset star status if bird is dead and out of screen
			player.star.isShooting = false;
			player.star.setSpeed(0.8f*10);		
		}
		resetObstacle();
        if (player.score %3 == 0)
            speed = -28.f;
	}
	// dead bird falls on ground
	if (speedY != 0 && sprite.getPosition().y > HEIGHT-100) {
		speedY = 0;
		// when dead bird falls on ground allow player to shoot again
		player.star.isShooting = false;
		player.star.setSpeed(0.8f*10);
	}

	// CHECK COLLISION (rowNo = 0 means bird is alive and can kill player)
	if (rowNo == 0 && sprite.getGlobalBounds().intersects(player.globalBounds())) {
		player.kill();
		speed = 0.f;
	}

	// bird kill
	if (sprite.getGlobalBounds().intersects(player.star.globalBounds())) {
		starHitSound.play();
		player.score++;
		// start bird dead animation
		rowNo = 1;
		speed = SCROLL_SPEED;
		speedY = 1.f;
		// set star speed to 0 after killing bird and allow to throw star only after dead bird falls on ground
		player.star.setPos(sf::Vector2f(0, 0)); 
		player.star.setSpeed(0.f);
	}
}

void Bird::resetObstacle() {
	speedY = 0;
	rowNo = 0;
	sprite.setPosition(WIDTH * 2.f + rand()%WIDTH, HEIGHT-200);
	speed = 2*SCROLL_SPEED - (rand() % 8); // -rand() done becz SCROLL_SPEED is -ve and bird moves left
}


Saw::Saw()
{
	this->speed = SCROLL_SPEED;
	this->switchTime = 0.05f;

	if (!texture.loadFromFile("images/jungle/SAW.png"))
		throw("err, cant load image");
	sprite.setTexture(texture);
	// sprite.setScale(0.9f, 0.9f); // default scale 1.f
	sprite.setPosition(WIDTH, HEIGHT - 135);
	objectWidth = texture.getSize().x/4;
	uvRect = sf::IntRect(0, 0, objectWidth, texture.getSize().y);
	sprite.setTextureRect(uvRect);
}

void Saw::update(Player& player, float deltaTime) {
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		imageNo++;
		if (imageNo > 3)
			imageNo = 0;
		uvRect.left = imageNo * objectWidth;
		sprite.setTextureRect(uvRect);
	}
	
	sprite.move(speed, 0);
	if (sprite.getPosition().x < -objectWidth) {
		sprite.setPosition(WIDTH*1.5f, sprite.getPosition().y);
	}

	// CHECK COLLISION
	if (sprite.getGlobalBounds().intersects(player.globalBounds())) {
		player.kill();
	}
}

void Saw::resetObstacle() {
	sprite.setPosition(WIDTH, sprite.getPosition().y); // width only
}


Cactus::Cactus(): speed(SCROLL_SPEED) {
	if (!rectTexture.loadFromFile("images/jungle/cactus.png"))
		throw("err, cant load image");
	shape.setSize(sf::Vector2f(100, 150)); // HEIGHT = 125 and yPos = -150 if difficult
	shape.setTexture(&rectTexture);
	shape.setPosition(WIDTH * 2.f, HEIGHT-160);
	objectWidth = shape.getGlobalBounds().width;	
	objectHeight = shape.getGlobalBounds().height;	
	// shape.setOutlineThickness(1.f);
	// shape.setOutlineColor(sf::Color::Red);
}

void Cactus::update(Player& player, float deltaTime) {
	shape.move(speed, 0);
	if (shape.getPosition().x < -objectWidth)
		shape.setPosition(WIDTH*1.5f, shape.getPosition().y);
	// CHECK COLLISION
	if (shape.getGlobalBounds().intersects(player.globalBounds())) {
		player.kill();
	}
}

void Cactus::resetObstacle() {
	shape.setPosition(WIDTH*1.5f, shape.getPosition().y);
}

Spike::Spike(): speed(SCROLL_SPEED) {
	if (!rectTexture.loadFromFile("images/jungle/spike.png"))
		throw("err, cant load image");
	shape.setSize(sf::Vector2f(48, 500));
	shape.setTexture(&rectTexture);
	shape.setPosition(WIDTH * 1.5f, 0);
	objectWidth = shape.getGlobalBounds().width;	
	objectHeight = shape.getGlobalBounds().height;	

	hitBox.setSize(sf::Vector2f(24, 24));
	hitBox.setPosition(shape.getPosition().x+12, shape.getPosition().y+objectHeight-24);
	hitBox.setFillColor(sf::Color(165,42,42));
	// shape.setOutlineThickness(1.f);
	// shape.setOutlineColor(sf::Color::Red);
}

void Spike::update(Player& player, float deltaTime) {
	shape.move(speed, 0);
	if (shape.getPosition().x < -100) {
		shape.setPosition(WIDTH*1.5f, 0);
	}

	// HIT BOX
	hitBox.setPosition(shape.getPosition().x+12, shape.getPosition().y+objectHeight-24);

	// CHECK COLLISION
	if (player.isJumping && shape.getGlobalBounds().intersects(player.globalBounds()))
		player.kill();
	else if (hitBox.getGlobalBounds().intersects(player.globalBounds()))
		player.kill();
}

void Spike::resetObstacle() {
	shape.setPosition(WIDTH*2.f, 0);
}


Enemy::Enemy() {
    obstacle[0] = &bird;
    obstacle[1] = &saw;
    obstacle[2] = &cactus;
    obstacle[3] = &spike;
}

void Enemy::update(float deltaTime, Player& player) {
    obstacle[0]->update(player, deltaTime); // bird
    obstacle[1]->update(player, deltaTime); // saw
    obstacle[2]->update(player); // cactus
    obstacle[3]->update(player); // spike
}

void Enemy::resetEnemy() {
    for (int i=0; i<4; i++)
        obstacle[i]->resetObstacle();
}

void Enemy::drawTo(sf::RenderWindow& window) {
	bird.drawTo(window);
	saw.drawTo(window);
	cactus.drawTo(window);
	spike.drawTo(window);
	// window.draw(spike.hitBox);
}