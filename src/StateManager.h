#pragma once
#include "raylib.h"

class Player;

class StateManager
{
private:

	Player* player;
	
	float score;
	int multiplier;

	bool isGameOver;

	float timer;
	float multiplierTimer;

	float speedMultiplier;     
	float speedMultiplierTimer; 

public:
	StateManager(Player* player);
	~StateManager() {}

	void Update();
	void Draw();

	void SetMultiplier(int mult, float duration);
	void SetSpeedMultiplier(float mult, float duration);

	float GetScore();
	bool IsGameOver();
	void AddScore(int points);

	void CheckGameOver();
};

