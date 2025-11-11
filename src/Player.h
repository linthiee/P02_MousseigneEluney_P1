#pragma once
#include "Entity.h"
#include "StateManager.h"

class Player : public Entity
{
private:

	StateManager* manager;

	int score;
	int lives;
	Vector2 velocity;
	float speed;
	float baseSpeed;

	bool isInvincible;
	float invincibilityTimer;
	float invincibilityDuration; 

public:

	Player(Vector2 pos, int texID, float width, float height);
	~Player() {}

	void SetStateManager(StateManager* stateManager);

	int GetLife();
	void UpdateLife(int life);

	void IsCollidingWith(Entity* otherEntity) override;
	void TakeDamage() override;

	bool IsInvincible();

	void ActivateScoreMultiplier(int multiplier, float duration);
	void ActivateSpeedMultiplier(float multiplier, float duration);
	void ActivateAddScore(int value);

	void SetSpeed(float newSpeed); 
	float GetBaseSpeed();          

	void Update() override;
	void Draw() override;
};