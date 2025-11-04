#pragma once
#include "raylib.h"

class Entity
{
protected:

	Vector2 position;
	int textureID;
	float width;
	float height;

public:

	Entity(Vector2 pos, int texID, float width, float height);
	~Entity() {}

	Vector2 GetPosition() const;
	int GetTextureID() const;
	float GetWidth() const;
	float GetHeight() const;

	void SetPosition(Vector2 pos);

	//virtual void IsCollidingWith(Entity* otherEntity);

	virtual void Update();
	virtual void Draw();
};

