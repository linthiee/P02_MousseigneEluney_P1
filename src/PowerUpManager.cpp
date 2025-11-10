#include "PowerUpManager.h"
#include "Collectible.h"
#include "ExtraLife.h"
#include "ScoreMultiplyer.h"

PowerUpManager::PowerUpManager(float spawnInterval)
{
	intervalSpawn = spawnInterval;
	spawnTimer = spawnInterval;
}

void PowerUpManager::Update(float deltaT, std::vector<Entity*>& entities, int currentPowerUpCount)
{
    if (currentPowerUpCount > 0)
    {
        spawnTimer = intervalSpawn;
        return;
    }

    spawnTimer -= deltaT;

    if (spawnTimer <= 0.0f)
    {
        spawnTimer = intervalSpawn;

        int randomType = GetRandomValue(0, 2);
        Collectible* newPowerUp = nullptr;

        Vector2 randomPos = { (float)GetRandomValue(50, 750), (float)GetRandomValue(50, 400) };

        if (randomType == 0)
        {
            //newPowerUp = new ExtraLife(randomPos, 0, 20.0f, 20.0f);
        }
		//else if (randomType == 1)
  //      {
  //           newPowerUp = new ScoreMultiplyer(randomPos, 0, 20.0f, 20.0f);
  //      }
  //      else
  //      {
		//	// newPowerUp = new Shield(randomPos, ...);
  //      }
        newPowerUp = new ScoreMultiplyer(randomPos, 0, 20.0f, 20.0f);

         if (newPowerUp != nullptr)
         {
             entities.push_back(newPowerUp);
         }
    }
}
