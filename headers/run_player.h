#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "entity.h"


class Star: public SpriteEntity, public AnimationEntity {
public:
	bool isShooting = false;
	Star();
	void setPos(sf::Vector2f pos);
	void setSpeed(float velocity);
	void update(float deltaTime);
	sf::FloatRect globalBounds();
};

class Player: public SpriteEntity {
private:
	sf::IntRect uvRect;
	int playerHeight, playerWidth;
	int imageNo = 0, rowNo = 0; // (Idle-0, Dead-1, Jump-2, Run-3, Slide-4)
	
	struct switchTimes{
		float run = 0.05f, jump = 0.1f, dead = 0.5f, idle = 0.03f, slide = 0.08f;
	}switchTime;
	float totalTime = 0.0f;
	float deltaTime = 0.f;

	sf::Sound jumpSound, deathSound;
	sf::SoundBuffer jumpBuffer, deathBuffer;

public:
	Star star;
	int score = 0;
	bool isJumping = false, isIdle = true, isSliding = false, isDead = false, isDeadAnimationOver = false;
private:
	void idle();
	void run();
	void jump();
	void slide();
	void dead();
	void resetPosition();

public:
	Player();
	void update(float deltaTime);
	void kill();
	void resetPlayer();
	sf::FloatRect globalBounds();
};