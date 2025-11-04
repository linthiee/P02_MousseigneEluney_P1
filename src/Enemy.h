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

public:

	Enemy(Vector2 pos, int texID, float width, float height);
	~Enemy() {}

	void Initialize(std::vector<Enemy*> enemies);
	void Spawn();

	void Update(Player* player);
	void Draw() override;
};

