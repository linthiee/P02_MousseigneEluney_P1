#pragma once
#include "Entity.h"

class Player : public Entity
{
private:

	int score;
	float life;
	Vector2 velocity;
	float speed;

public:

	Player(Vector2 pos, int texID, float width, float height);
	~Player() {}

	//void IsCollidingWith(Entity* otherEntity) override;

	void Update() override;
	void Draw() override;
};