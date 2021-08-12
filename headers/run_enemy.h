#pragma once
#include "entity.h"
#include "run_player.h"


class Bird: public SpriteEntity, public AnimationEntity {
	float speedY = 0;
	sf::Sound starHitSound;
	sf::SoundBuffer starHitBuffer;
public:
	Bird();
	void update(float deltaTime, Player& player);
	void resetBird();
};


class Saw: public SpriteEntity, public AnimationEntity {
public:
	Saw();
	void update(float deltaTime, Player& player);
	void resetSaw();
};


class Cactus: public RectEntity {
	float speed;
	sf::FloatRect globalBounds();
	sf::Texture fireTexture;
	bool isCactus = true;
public:
	Cactus();
	void update(Player& player);
	void resetCactus();
};


class Spike: public RectEntity {
	float speed;
public:
	sf::RectangleShape hitBox;
	Spike();
	void update(Player& player);
	void resetSpike();
};

class Enemy {
	Bird bird;
	Saw saw;
	Cactus cactus;
	Spike spike;
public:
	// Enemy();
	void resetEnemy();
	void update(float deltaTime, Player& player);
	void drawTo(sf::RenderWindow& window);
};