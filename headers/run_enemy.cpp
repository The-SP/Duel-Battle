#include "run_enemy.h"
#include "global.h"

Bird::Bird()
{
	this->speed = 2.5*SCROLL_SPEED;
	this->switchTime = 0.15f;

	if (!texture.loadFromFile("images/jungle/birds.png"))
		throw("err, cant load image");
	sprite.setTexture(texture);

	sprite.setScale(0.15f, 0.15f);
	this->objectWidth = texture.getSize().x/2; 
	this->objectHeight = texture.getSize().y/2;
	uvRect = sf::IntRect(0, 0, objectWidth, objectHeight);
	sprite.setTextureRect(uvRect);
	sprite.setPosition(WIDTH*2, HEIGHT-200);
}

void Bird::update(float deltaTime, Player& player) {
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
	if (sprite.getPosition().x < -50) {
		resetBird();
	}
	if (sprite.getPosition().y > HEIGHT-100) {
			speedY = 0;
	}

	// CHECK COLLISION (rowNo = 0 means bird is alive and can kill player)
	if (rowNo == 0 && sprite.getGlobalBounds().intersects(player.globalBounds())) {
		// kill bird if land on top
		if (player.globalBounds().left > sprite.getPosition().x/2 && player.globalBounds().top+player.globalBounds().height >= sprite.getPosition().x) {
			player.score++;
			// start dead animation
			rowNo = 1;
			speed = SCROLL_SPEED;
			speedY = 0.3f;
			player.star.setPos(sf::Vector2f(0, 0));
			player.star.isShooting = false;			
		} else {
			player.kill();
			speed = 0.f;
		}
	}

	// bird kill
	if (sprite.getGlobalBounds().intersects(player.star.globalBounds())) {
		player.score++;
		// start dead animation
		rowNo = 1;
		speed = SCROLL_SPEED;
		speedY = 0.3f;
		player.star.setPos(sf::Vector2f(0, 0));
		player.star.isShooting = false;
	}
}

void Bird::resetBird() {
	speedY = 0;
	rowNo = 0;
	sprite.setPosition(WIDTH * 2.5f + rand()%WIDTH, HEIGHT-200);
	speed = 2*SCROLL_SPEED - (rand() % 100) * 0.02f;	
}


Saw::Saw()
{
	this->speed = SCROLL_SPEED;
	this->switchTime = 0.05f;

	if (!texture.loadFromFile("images/jungle/SAW.png"))
		throw("err, cant load image");
	sprite.setTexture(texture);
	sprite.setScale(0.9f, 0.9f);
	sprite.setPosition(WIDTH, HEIGHT - 135);
	objectWidth = texture.getSize().x/4;
	uvRect = sf::IntRect(0, 0, objectWidth, texture.getSize().y);
	sprite.setTextureRect(uvRect);
}

void Saw::update(float deltaTime, Player& player) {
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
		// isOutOfScreen = true;
		sprite.setPosition(WIDTH*1.5f, sprite.getPosition().y);
	}

	// CHECK COLLISION
	if (sprite.getGlobalBounds().intersects(player.globalBounds())) {
		player.kill();
	}
}

void Saw::resetSaw() {
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

void Cactus::update(Player& player) {
	shape.move(speed, 0);
	if (shape.getPosition().x < -objectWidth)
		shape.setPosition(WIDTH*1.5f, shape.getPosition().y);
	// CHECK COLLISION
	if (shape.getGlobalBounds().intersects(player.globalBounds())) {
		player.kill();
	}
}

void Cactus::resetCactus() {
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

void Spike::update(Player& player) {
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

void Spike::resetSpike() {
	shape.setPosition(WIDTH*2.f, 0);
}


void Enemy::update(float deltaTime, Player& player) {
	bird.update(deltaTime, player);
	saw.update(deltaTime, player);
	cactus.update(player);
	spike.update(player);
}

void Enemy::resetEnemy() {
	bird.resetBird();
	saw.resetSaw();
	cactus.resetCactus();
	spike.resetSpike();
}

void Enemy::drawTo(sf::RenderWindow& window) {
	bird.drawTo(window);
	saw.drawTo(window);
	cactus.drawTo(window);
	spike.drawTo(window);
	// window.draw(spike.hitBox);
}

