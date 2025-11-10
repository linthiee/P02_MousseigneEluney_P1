#include "Entity.h"

Entity::Entity(Vector2 pos, int texID, float width, float height) : position(pos), textureID(texID), width(width), height(height)
{
	deleteEntity = false;
}

Vector2 Entity::GetPosition() const { return position; }
int Entity::GetTextureID() const { return textureID; }
float Entity::GetWidth() const { return width; }
float Entity::GetHeight() const { return height; }

void Entity::SetPosition(Vector2 pos) { position = pos; }

void Entity::DeleteEntity()
{
    deleteEntity = true;
}

bool Entity::IsEntityDeleted()
{
    return deleteEntity;
}

void Entity::IsCollidingWith(Entity* otherEntity)
{
    otherEntity = nullptr;
}

void Entity::TakeDamage() {}

void Entity::Update() {}

void Entity::Draw()
{
    Texture texture;

    texture.id = static_cast<unsigned int>(textureID);
    texture.width = static_cast<int>(width);
    texture.height = static_cast<int>(height);

	DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
}
