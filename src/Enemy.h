#pragma once
#include "Entity.h"
#include "Player.h"

#include <vector>

class Enemy : public Entity
{
private:

	float life;
	Vector2 velocity;
	float speed;

	Player* target;

public:

	Enemy(Vector2 pos, int texID, float width, float height, Player* target);
	~Enemy() {}

	void IsCollidingWith(Entity* otherEntity) override;

	void Update() override; 
	void Draw() override;
};

