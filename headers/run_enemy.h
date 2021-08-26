#pragma once
#include "entity.h"
#include "run_player.h"

class Obstacle {
public:
    virtual void update(Player& player, float deltaTime = 0.f) = 0;
    virtual void resetObstacle() = 0;
};

class Bird: public SpriteEntity, public AnimationEntity, public Obstacle{
	float speedY = 0;
	sf::Sound starHitSound;
	sf::SoundBuffer starHitBuffer;
public:
	Bird();
	void update(Player& player, float deltaTime = 0.f);
    void resetObstacle();
};


class Saw: public SpriteEntity, public AnimationEntity, public Obstacle {
public:
	Saw();
	void update(Player& player, float deltaTime = 0.f);
    void resetObstacle();
};


class Cactus: public RectEntity, public Obstacle {
	float speed;
	sf::FloatRect globalBounds();
	sf::Texture fireTexture;
	bool isCactus = true;
public:
	Cactus();
	void update(Player& player, float deltaTime = 0.f);
    void resetObstacle();
};


class Spike: public RectEntity, public Obstacle {
	float speed;
public:
	sf::RectangleShape hitBox;
	Spike();
	void update(Player& player, float deltaTime = 0.f);
    void resetObstacle();
};

class Enemy {
	Bird bird;
	Saw saw;
	Cactus cactus;
	Spike spike;
    Obstacle* obstacle[4];
public:
	Enemy();
	void resetEnemy();
	void update(float deltaTime, Player& player);
	void drawTo(sf::RenderWindow& window);
};